// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.


#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>
#include <iostream>
#include "RobotContainer.h"
#include "subsystems/SubArm.h"


//./gradlew clean

SubArm::SubArm() {
  frc::SmartDashboard::PutData("Arm/Arm Motor 1: ", (wpi::Sendable*)&_armMotor1);
  _armMotor1.SetConversionFactor(1 / GEAR_RATIO);
  _armMotor1.SetPIDFF(P, I, D, F);
  _armMotor1.ConfigSmartMotion(MAX_VEL, MAX_ACCEL, TOLERANCE);

  frc::SmartDashboard::PutData("Arm/Arm Motor 2: ", (wpi::Sendable*)&_armMotor2);
  _armMotor2.SetConversionFactor(1 / GEAR_RATIO_2);
  _armMotor2.SetPIDFF(P_2, I_2, D_2, F_2);
  _armMotor2.ConfigSmartMotion(MAX_VEL_2, MAX_ACCEL_2, TOLERANCE_2);

  frc::SmartDashboard::PutData("Arm/Mechanism Display", &_doubleJointedArmMech);
  frc::SmartDashboard::PutNumber("Arm/y_coord input: ", 0);
  frc::SmartDashboard::PutNumber("Arm/x_coord input: ", 0);

  // _armMotor1Follow.Follow(_armMotor1);
  _armMotor1.SetInverted(true);
}

// This method will be called once per scheduler runss
void SubArm::Periodic() {
  frc::SmartDashboard::PutNumber("Arm/Bus Voltage", _armMotor1.GetBusVoltage());
  frc::SmartDashboard::PutNumber("Arm/Current Output", _armMotor1.GetOutputCurrent());
  frc::SmartDashboard::PutNumber("Arm/Bus Voltage Follow", _armMotor1Follow.GetBusVoltage());
  frc::SmartDashboard::PutNumber("Arm/Current Output Follow", _armMotor1Follow.GetOutputCurrent());
  
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
  _armMotor1.SetSmartMotionTarget(bottomAngle);
  _armMotor2.SetSmartMotionTarget(topAngle);
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

  return {armTopAngle + armBottomAngle, armBottomAngle};
}

void SubArm::ArmPos(units::meter_t x, units::meter_t y) {
  // double x_coord = x.value();
  // double y_coord = y.value();

  // double armTopAngleFracbottom = pow(x_coord, 2.0) + pow(y_coord, 2.0) - pow(ARM_LENGTH.value(), 2.0) - pow(ARM_LENGTH_2.value(), 2.0);
  // double armTopAngleFractop = 2.0 * ARM_LENGTH.value() * ARM_LENGTH_2.value();
  // units::radian_t armTopAngle{-1 * (acos(armTopAngleFracbottom / armTopAngleFractop))};

  // double armBottomAngleFracbottom = ARM_LENGTH_2.value() * sin(armTopAngle.value());
  // double armBottomAngleFractop = ARM_LENGTH.value() + ARM_LENGTH_2.value() * cos(armTopAngle.value());
  // double statement1 = atan(y_coord / x_coord);
  // double statement2 = atan(armBottomAngleFracbottom / armBottomAngleFractop);
  // units::radian_t armBottomAngle{statement1 - statement2};

  // DriveTo(armBottomAngle, armTopAngle);
  auto armAngle = InverseKinmetics(x,y);
  DriveTo(armAngle.second, armAngle.first);
}

void SubArm::CubeConeSwitch() {}

void SubArm::SimulationPeriodic() {
  _armSim.SetInputVoltage(_armMotor1.GetSimVoltage());
  _armSim.Update(20_ms);

  _armSim2.SetInputVoltage(_armMotor2.GetSimVoltage());
  _armSim2.Update(20_ms);

  auto armAngle = _armSim.GetAngle();
  auto armVel = _armSim.GetVelocity();
  _armMotor1.UpdateSimEncoder(armAngle, armVel);

  auto x_coord = _armSim2.GetAngle();
  auto armVel2 = _armSim2.GetVelocity();
  _armMotor2.UpdateSimEncoder(x_coord, armVel2);

  _arm1Ligament->SetAngle(armAngle);
  _arm2Ligament->SetAngle(x_coord - armAngle);
}

void SubArm::ArmResettingPos() {
  _armMotor1.SetPosition(0_deg);
  _armMotor2.SetPosition(0_deg);
}

bool SubArm::CheckPosition() {
  bool s1 = units::math::abs(_armMotor1.GetPosition() - targetBottomAngle) < 0.05_rad;
  bool s2 = units::math::abs(_armMotor2.GetPosition() - targetTopAngle) < 0.05_rad;
  return s1 && s2;
}