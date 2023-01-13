// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubArm.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <cmath>
#include <iostream>

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
  frc::SmartDashboard::PutNumber("Arm/bottomAngle input: ", 0);
  frc::SmartDashboard::PutNumber("Arm/topAngle input: ", 0);
  frc::SmartDashboard::PutNumber("Arm/Arm2 offset: ", 1);

  _armMotor1Follow.Follow(_armMotor1);
  _armMotor1.SetInverted(true);
}

// This method will be called once per scheduler runss
void SubArm::Periodic() {
    frc::SmartDashboard::PutNumber("Arm/Bus Voltage", _armMotor1.GetBusVoltage());
    frc::SmartDashboard::PutNumber("Arm/Current Output", _armMotor1.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Arm/Bus Voltage Follow", _armMotor1Follow.GetBusVoltage());
    frc::SmartDashboard::PutNumber("Arm/Current Output Follow", _armMotor1Follow.GetOutputCurrent());

    units::degree_t bottomAngle{frc::SmartDashboard::GetNumber("Arm/bottomAngle input: ", 0)};
    units::degree_t topAngle{frc::SmartDashboard::GetNumber("Arm/topAngle input: ", 0)};
    DriveTo(bottomAngle, topAngle);
}

void SubArm::DriveTo(units::degree_t deg1, units::degree_t deg2) {
  _armMotor1.SetSmartMotionTarget(deg1);
  _armMotor2.SetSmartMotionTarget(deg2 + deg1); 
}

void SubArm::ArmPos(units::meter_t x, units::meter_t y) {
  double x_coord = x.value();
  double y_coord = y.value();

  double topAngleFracbottom = pow(x_coord, 2.0) + pow(y_coord, 2.0) - pow(ARM_LENGTH.value(), 2.0) - pow(ARM_LENGTH_2.value(), 2.0);
  double topAngleFractop = 2.0 * ARM_LENGTH.value() * ARM_LENGTH_2.value();
  units::radian_t topAngle{-1 * (acos(topAngleFracbottom / topAngleFractop))};

  double bottomAngleFracbottom = ARM_LENGTH_2.value() * sin(topAngle.value());
  double bottomAngleFractop = ARM_LENGTH.value() + ARM_LENGTH_2.value() * cos(topAngle.value());
  double statement1 = atan(y_coord / x_coord);
  double statement2 = atan(bottomAngleFracbottom / bottomAngleFractop);
  units::radian_t bottomAngle{statement1 - statement2};

  //bottomAngle = bottom angle
  //topAngle = top angle
  DriveTo(bottomAngle * -1, topAngle);
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

  auto armtopAngle = _armSim2.GetAngle();
  auto armVel2 = _armSim2.GetVelocity();
  _armMotor2.UpdateSimEncoder(armtopAngle, armVel2);

  _arm1Ligament->SetAngle(armAngle * -1);
  _arm2Ligament->SetAngle(armtopAngle - armAngle);
}