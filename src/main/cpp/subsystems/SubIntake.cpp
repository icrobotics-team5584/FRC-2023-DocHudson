// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"

#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() {
  _leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  _leftMotor.SetSmartCurrentLimit(20);
  _rightMotor.SetSmartCurrentLimit(20);
}

// This method will be called once per scheduler run
void SubIntake::Periodic() {
   
frc::SmartDashboard::PutNumber("Intake/IntakeMotor",  _leftMotor.GetSimVoltage().value());
frc::SmartDashboard::PutNumber("Intake/OuttakeMotor", _rightMotor.GetSimVoltage().value());


}

void SubIntake::IntakeLeft(){
	_leftMotor.Set(-1);
}

void SubIntake::IntakeRight(){
	_rightMotor.Set(0.5);
}

void SubIntake::OuttakeLeft(){
	_leftMotor.Set(-0.5);
}

void SubIntake::OuttakeRight(){
	_rightMotor.Set(1);
}

void SubIntake::Stop(){
	_leftMotor.Set(0);
	_rightMotor.Set(0);
}

void SubIntake::BothExtended(){
    _solPnuematicsLeftBumper.Set(frc::DoubleSolenoid::Value::kForward);
    _solPnuematicsRightBumper.Set(frc::DoubleSolenoid::Value::kForward);
}

void SubIntake::BothRetracted(){
    _solPnuematicsLeftBumper.Set(frc::DoubleSolenoid::Value::kReverse);
    _solPnuematicsRightBumper.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SubIntake::OneExtended(){
    _solPnuematicsLeftBumper.Set(frc::DoubleSolenoid::Value::kForward);
}
void SubIntake::OneRetracted(){
    _solPnuematicsRightBumper.Set(frc::DoubleSolenoid::Value::kReverse);
}
