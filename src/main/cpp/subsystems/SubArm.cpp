// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>
#include <iostream>
#include "RobotContainer.h"
#include "subsystems/SubArm.h"
#include <frc2/command/commands.h>
#include <frc2/command/button/Trigger.h>
#include <frc/MathUtil.h>

//./gradlew clean

SubArm::SubArm() {
  frc::SmartDashboard::PutData("Arm/Arm Motor Bottom: ", (wpi::Sendable*)&_armMotorBottom);
  _armMotorBottom.SetConversionFactor(1 / GEAR_RATIO);
  _armMotorBottom.SetPIDFF(P, I, D, F);
  _armMotorBottom.ConfigSmartMotion(MAX_VEL, MAX_ACCEL, TOLERANCE);

  frc::SmartDashboard::PutData("Arm/Arm Motor Top: ", (wpi::Sendable*)&_armMotorTop);
  _armMotorTop.SetConversionFactor(1 / GEAR_RATIO_2);
  _armMotorTop.SetPIDFF(P_2, I_2, D_2, F_2);
  _armMotorTop.ConfigSmartMotion(MAX_VEL_2, MAX_ACCEL_2, TOLERANCE_2);

  frc::SmartDashboard::PutData("Arm/Mechanism Display", &_doubleJointedArmMech);
  frc::SmartDashboard::PutNumber("Arm/y_coord input: ", 0);
  frc::SmartDashboard::PutNumber("Arm/x_coord input: ", 0);
  frc::SmartDashboard::PutNumber("Arm/Bottom grav comp", _bottomArmGravityFF.kG.value());
  frc::SmartDashboard::PutNumber("Arm/Top grav comp", _topArmGravityFF.kG.value());

  _armMotorTop.SetInverted(true);
  _armMotorBottomFollow.Follow(_armMotorBottom);
  _armMotorTopFollow.Follow(_armMotorTop);

  _armMotorTop.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _armMotorBottom.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _armMotorTopFollow.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _armMotorBottomFollow.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  _topEncoder.SetInverted(true);
  _armMotorTop.UseAbsoluteEncoder(_topEncoder);

  _armMotorBottom.UseAbsoluteEncoder(_bottomEncoder);
  _bottomEncoder.SetZeroOffset(0.093);

  // Gravity map (currently unused and untuned, bottom arm is pretty geared down anyway and isn't affected much
  // by gravity)
  _bottomArmGravFFMap.insert(0_tr, 1_V);      // When top arm is at 0_tr, bottom arm uses 1_V as its grav FF
  _bottomArmGravFFMap.insert(-0.1_tr, 0.7_V); // When top arm is at 0.1_tr, bottom arm uses 0.7_V as its grav FF
  _bottomArmGravFFMap.insert(-0.2_tr, 0.4_V); // etc..
  _bottomArmGravFFMap.insert(-0.3_tr, 0.1_V);

  frc::SmartDashboard::PutNumber("Arm/Back sensor input: ", 0);
}

// This method will be called once per scheduler runss
void SubArm::Periodic() {
  frc::SmartDashboard::PutNumber("Arm/bottom to top arm turns", GetBottomToTopArmAngle().value());
  frc::SmartDashboard::PutNumber("Arm/ground to top arm turns", GetGroundToTopArmAngle().value());
  frc::SmartDashboard::PutNumber("Arm/top arm encoder", _topEncoder.GetPosition());
  frc::SmartDashboard::PutNumber("Arm/bottom arm encoder", _bottomEncoder.GetPosition());
  
  auto EEPos = GetEndEffectorPosition();
  frc::SmartDashboard::PutNumber("Arm/Current X", EEPos.X().value());
  frc::SmartDashboard::PutNumber("Arm/Current Y", EEPos.Y().value());
  DashboardInput();

  // Update gravity comp FF
  // Use zero for vel factor since we are only using these feedforward objects
  // for the gravity factor. Vel and accel is handeled by Spark Max Smart Motion.
  _topArmGravityFF.kG = frc::SmartDashboard::GetNumber("Arm/Top grav comp", _topArmGravityFF.kG.value())*1_V;
  _bottomArmGravityFF.kG = frc::SmartDashboard::GetNumber("Arm/Bottom grav comp", _bottomArmGravityFF.kG.value())*1_V;
  // _bottomArmGravityFF.kG = _bottomArmGravFFMap[CalcGroundToTopArm()];
  auto topGravFF = _topArmGravityFF.Calculate(GetGroundToTopArmAngle(), 0_rad_per_s);
  auto bottomGravFF = _bottomArmGravityFF.Calculate(_bottomEncoder.GetPosition()*1_tr, 0_rad_per_s);
  if (_armMotorTop.GetControlType() == rev::CANSparkMax::ControlType::kSmartMotion &&
      _armMotorBottom.GetControlType() == rev::CANSparkMax::ControlType::kSmartMotion) {
    _armMotorTop.SetSmartMotionTarget(_armMotorTop.GetPositionTarget(), topGravFF);
    _armMotorBottom.SetSmartMotionTarget(_armMotorBottom.GetPositionTarget(), bottomGravFF);
  }

  // Update mech2d display
  _arm1Ligament->SetAngle(_bottomEncoder.GetPosition()*1_tr);
  _arm2Ligament->SetAngle(GetBottomToTopArmAngle());

  static bool wasOnTarget = false;

  if(CheckPosition(10_deg) && !wasOnTarget) {
    _armMotorBottom.SetPIDFF(P,I,D,15);
    _armMotorTop.SetPIDFF(P_2,I_2,D_2,15);
    frc2::cmd::Print("drivebase/set FF to 15");
  } else if (!CheckPosition(10_deg) && wasOnTarget) {
    _armMotorBottom.SetPIDFF(P,I,D,30);
    _armMotorTop.SetPIDFF(P_2,I_2,D_2,30);
    frc2::cmd::Print("drivebase/set FF to 30");
  };

  wasOnTarget = CheckPosition(10_deg);
}

void SubArm::DashboardInput(){
  static auto prevXRequest = 0_m;
  static auto prevYRequest = 0_m; 

  units::centimeter_t x_coord{frc::SmartDashboard::GetNumber("Arm/x_coord input: ", 0)};
  units::centimeter_t y_coord{frc::SmartDashboard::GetNumber("Arm/y_coord input: ", 0)};

  if((prevXRequest != x_coord) or (prevYRequest != y_coord)){
    ArmPos(x_coord, y_coord);
  } 
  
  prevYRequest = y_coord;
  prevXRequest = x_coord;
}

void SubArm::DriveTo(units::degree_t bottomAngle, units::degree_t topAngle) {
  _armMotorBottom.SetSmartMotionTarget(bottomAngle);
  frc::SmartDashboard::PutNumber("Arm/Top target before addition", topAngle.value());
  frc::SmartDashboard::PutNumber("Arm/Top target after addition", (topAngle+360_deg).convert<units::turns>().value());
  _armMotorTop.SetSmartMotionTarget(TopArmAngleToEncoderAngle(topAngle));
}

void SubArm::DriveBottomAt(double bottomPower) {
  _armMotorBottom.Set(bottomPower);
}

std::optional<SubArm::IKResult> SubArm::InverseKinmetics(units::meter_t x, units::meter_t y) {
  double x_coord = x.value();
  double y_coord = y.value();

  double armTopAngleFracbottom = pow(x_coord, 2.0) + pow(y_coord, 2.0) - pow(ARM_LENGTH.value(), 2.0) - pow(ARM_LENGTH_2.value(), 2.0);
  double armTopAngleFractop = 2.0 * ARM_LENGTH.value() * ARM_LENGTH_2.value();
  units::radian_t armTopAngle{-1 * (acos(armTopAngleFracbottom / armTopAngleFractop))};

  double armBottomAngleFracbottom = ARM_LENGTH_2.value() * sin(armTopAngle.value());
  double armBottomAngleFractop = ARM_LENGTH.value() + ARM_LENGTH_2.value() * cos(armTopAngle.value());
  double statement1 = atan(y_coord / x_coord);
  double statement2 = atan(armBottomAngleFracbottom / armBottomAngleFractop);
  units::radian_t armBottomAngle{statement1 - statement2};

  // Some X Y targets cause a bad IK output since the arm can't reach there, catch them here
  if (std::isnan(armBottomAngle.value()) || std::isnan(armTopAngle.value())) {
    return {};
  }
  return IKResult{armBottomAngle, armTopAngle};
}

void SubArm::ArmPos(units::meter_t x, units::meter_t y) {
  auto ikResult = InverseKinmetics(x,y);
  if (ikResult.has_value()) {
    auto [bottomAngle, topAngle] = ikResult.value();
    _endEffectorTarget = {x, y};
    DriveTo(bottomAngle, topAngle);
  }
}

void SubArm::SimulationPeriodic() {
  _armSim.SetInputVoltage(_armMotorBottom.GetSimVoltage());
  _armSim.Update(20_ms);

  _armSim2.SetInputVoltage(_armMotorTop.GetSimVoltage());
  _armSim2.Update(20_ms);

  auto armAngle = _armSim.GetAngle();
  auto armVel = _armSim.GetVelocity();
  _armMotorBottom.UpdateSimEncoder(armAngle, armVel);

  auto armAngle2 = _armSim2.GetAngle();
  auto armVel2 = _armSim2.GetVelocity();
  _armMotorTop.UpdateSimEncoder(armAngle2, armVel2);
}

units::turn_t SubArm::GetBottomToTopArmAngle() {
  auto topAngle = frc::RobotBase::IsSimulation() ? _armMotorTop.GetPosition()
                                                 : _topEncoder.GetPosition()*1_tr;
  return frc::InputModulus(topAngle + 1_tr, -0.5_tr,
                           0.5_tr);
}

units::turn_t SubArm::GetGroundToTopArmAngle() {
  return _bottomEncoder.GetPosition()*1_tr + GetBottomToTopArmAngle();
}

units::turn_t SubArm::TopArmAngleToEncoderAngle(units::turn_t topArmAngle) {
  return frc::RobotBase::IsSimulation()
             ? topArmAngle
             : frc::InputModulus(topArmAngle + 1_tr, 0_tr, 1_tr);
}

frc::Translation2d SubArm::GetEndEffectorPosition() {
  frc::Rotation2d groundToTop {units::radian_t{GetGroundToTopArmAngle()}};
  frc::Rotation2d groundToBottom {units::radian_t{_bottomEncoder.GetPosition()*1_tr}};
  frc::Translation2d topPos {ARM_LENGTH_2, groundToTop};
  frc::Translation2d bottomPos { ARM_LENGTH, groundToBottom };
  return topPos + bottomPos;
}

frc::Translation2d SubArm::GetEndEffectorTarget() {
  return _endEffectorTarget;
}

void SubArm::ArmResettingPos() {
  _armMotorBottom.SetPosition(90_deg);
  // No need to set the top arm position since we are using an absolute encoder
}

bool SubArm::CheckPosition(units::degree_t tolerance) {
  auto topArmError = frc::RobotBase::IsSimulation()
          ? _armMotorTop.GetPosError()
          : _topEncoder.GetPosition() * 1_tr - _armMotorTop.GetPositionTarget();

  auto bottomArmError = frc::RobotBase::IsSimulation()
          ? _armMotorBottom.GetPosError()
          : _bottomEncoder.GetPosition() * 1_tr - _armMotorBottom.GetPositionTarget();
          
  bool bottomOnTarget = units::math::abs(bottomArmError) < tolerance;
  bool topOnTarget = units::math::abs(topArmError) < tolerance;
  return bottomOnTarget && topOnTarget;
}

bool SubArm::LocatingSwitchIsHit() {
  return !_bottomSensor.Get();
}

void SubArm::SetIdleMode(rev::CANSparkMax::IdleMode idleMode) {
  _armMotorTop.SetIdleMode(idleMode);
  _armMotorBottom.SetIdleMode(idleMode);
  _armMotorTopFollow.SetIdleMode(idleMode);
  _armMotorBottomFollow.SetIdleMode(idleMode);
}
