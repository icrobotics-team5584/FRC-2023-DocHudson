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
frc::SmartDashboard::PutNumber("RightBumper", _solPneumaticsRightBumper.Get());
frc::SmartDashboard::PutNumber("LeftBumper", _solPneumaicsLeftBumper.Get());
}

void SubIntake::SimulationPeriodic() {
//frc::SmartDashboard::PutNumber("Intake/IntakeMotor",  _leftMotor.GetSimVoltage().value());
//frc::SmartDashboard::PutNumber("Intake/OuttakeMotor", _rightMotor.GetSimVoltage().value());
}


void SubIntake::IntakeLeft(){
	_leftMotor.Set(1);
}

void SubIntake::IntakeRight(){
	_rightMotor.Set(-0.5);
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

void SubIntake::BothBumperExtended(){
    _solPneumaicsLeftBumper.Set(frc::DoubleSolenoid::Value::kForward);
    _solPneumaticsRightBumper.Set(frc::DoubleSolenoid::Value::kForward);
}

void SubIntake::BothBumperRetracted(){
    _solPneumaicsLeftBumper.Set(frc::DoubleSolenoid::Value::kReverse);
    _solPneumaticsRightBumper.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SubIntake::LeftBumperExtended(){
    _solPneumaicsLeftBumper.Set(frc::DoubleSolenoid::Value::kForward);
}

void SubIntake::LeftBumperRetracted(){
	_solPneumaicsLeftBumper.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SubIntake::RightBumperRetracted(){
	_solPneumaticsRightBumper.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SubIntake::RightBumperExtended(){
    _solPneumaticsRightBumper.Set(frc::DoubleSolenoid::Value::kForward);
}
