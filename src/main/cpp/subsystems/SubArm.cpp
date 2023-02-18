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

  _armMotorBottomFollow.Follow(_armMotorBottom);
  _armMotorTopFollow.Follow(_armMotorTop);

  _armMotorTop.SetInverted(true);

  // uncomment me to use absolute encoder
  // _armMotorTop.UseAbsoluteEncoder(_topEncoder);

  frc::SmartDashboard::PutNumber("Arm/Back sensor input: ", 0);
  frc2::Trigger([this] {
    return !_bottomSensor.Get();
  }).OnTrue(frc2::cmd::RunOnce([this] {
              ArmResettingPos();
            }).IgnoringDisable(true));
}

// This method will be called once per scheduler runss
void SubArm::Periodic() {
  frc::SmartDashboard::PutNumber("Arm/top arm true angle", _armMotorTop.GetPosition().value() - _armMotorBottom.GetPosition().value());
  
  DashboardInput();
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
  targetTopAngle = topAngle;
  targetBottomAngle = bottomAngle;
  _armMotorBottom.SetSmartMotionTarget(bottomAngle);
  _armMotorTop.SetSmartMotionTarget(topAngle);
}

std::pair<units::radian_t, units::radian_t> SubArm::InverseKinmetics(units::meter_t x, units::meter_t y) {
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

  // Some X Y targets cause a bad IK output, catch them and ask the arm to keep its current target
  if (armBottomAngle < 0_deg) {
    return {_armMotorBottom.GetPositionTarget(), _armMotorTop.GetPositionTarget()};
  }
  return {armTopAngle + armBottomAngle, armBottomAngle};
}

void SubArm::ArmPos(units::meter_t x, units::meter_t y) {
  auto armAngle = InverseKinmetics(x,y);
  DriveTo(armAngle.second, armAngle.first);
}

void SubArm::SimulationPeriodic() {
  _armSim.SetInputVoltage(_armMotorBottom.GetSimVoltage());
  _armSim.Update(20_ms);

  _armSim2.SetInputVoltage(_armMotorTop.GetSimVoltage());
  _armSim2.Update(20_ms);

  auto armAngle = _armSim.GetAngle();
  auto armVel = _armSim.GetVelocity();
  _armMotorBottom.UpdateSimEncoder(armAngle, armVel);

  auto x_coord = _armSim2.GetAngle();
  auto armVel2 = _armSim2.GetVelocity();
  _armMotorTop.UpdateSimEncoder(x_coord, armVel2);

  _arm1Ligament->SetAngle(armAngle);
  _arm2Ligament->SetAngle(x_coord - armAngle);
}

void SubArm::ArmResettingPos() {
  _armMotorBottom.SetPosition(126.33_deg);
  _armMotorTop.SetPosition(units::degree_t{126.33 - 166.79});
}

bool SubArm::CheckPosition() {
  bool s1 = units::math::abs(_armMotorBottom.GetPosition() - targetBottomAngle) < 0.05_rad;
  bool s2 = units::math::abs(_armMotorTop.GetPosition() - targetTopAngle) < 0.05_rad;
  return s1 && s2;
}