// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"

#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() {
  _leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

frc::SmartDashboard::PutData("Intake/Deploy Motor 1: ", (wpi::Sendable*)&_DeployMotor);

  _DeployMotor.SetPIDFF(P, I, D, F);

  _DeployMotor.SetPosition(0_tr);

  _leftMotor.SetSmartCurrentLimit(20);
  _rightMotor.SetSmartCurrentLimit(20);


}

// This method will be called once per scheduler run
void SubIntake::Periodic() {
   
frc::SmartDashboard::PutNumber("Intake/LeftIntakeMotor",  _leftMotor.GetSimVoltage().value());
frc::SmartDashboard::PutNumber("Intake/RightIntakeMotor", _rightMotor.GetSimVoltage().value());
frc::SmartDashboard::PutBoolean("Intake/SensesCone", SensesCone());
}

void SubIntake::SimulationPeriodic() {
frc::SmartDashboard::PutNumber("Intake/LeftIntakeMotor",  _leftMotor.GetSimVoltage().value());
frc::SmartDashboard::PutNumber("Intake/RightIntakeMotor", _rightMotor.GetSimVoltage().value());
}
void SubIntake::DeployIntake(){
	_DeployMotor.SetPositionTarget(0_tr);
}
void SubIntake::RetractIntake(){
	_DeployMotor.SetPositionTarget(0_tr);
}

void SubIntake::IntakeLeft(){
	_leftMotor.Set(0.2);
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

bool SubIntake::SensesCone(){return _coneSensor.Get();}
