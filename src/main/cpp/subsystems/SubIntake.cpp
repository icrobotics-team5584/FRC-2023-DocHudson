// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() {
    _spmLeftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    _spmRightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    _spmLeftMotor.SetSmartCurrentLimit(20);
    _spmRightMotor.SetSmartCurrentLimit(20);
}

// This method will be called once per scheduler run
void SubIntake::Periodic() {
   
}
void SubIntake::IntakeLeft(){
_spmLeftMotor.Set(-1);
}
void SubIntake::IntakeRight(){
_spmRightMotor.Set(0.5);
}
void SubIntake::OuttakeLeft(){
_spmLeftMotor.Set(-0.5);
}
void SubIntake::OuttakeRight(){
_spmRightMotor.Set(1);
}
void SubIntake::Stop(){
_spmLeftMotor.Set(0);
_spmRightMotor.Set(0);
}
