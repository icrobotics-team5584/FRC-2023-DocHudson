// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubClaw::SubClaw() {
    _spmLeftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    _spmRightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    _spmLeftMotor.SetSmartCurrentLimit(20);
    _spmRightMotor.SetSmartCurrentLimit(20);

    frc::SmartDashboard::PutData("Claw/IntakeMotor", (wpi::Sendable*)&_spmLeftMotor);
    frc::SmartDashboard::PutData("Claw/OuttakeMotor", (wpi::Sendable*)&_spmRightMotor);
}

// This method will be called once per scheduler run
void SubClaw::Periodic() {
   
}
void SubClaw::IntakeLeft(){
_spmLeftMotor.Set(-1);
}
void SubClaw::IntakeRight(){
_spmRightMotor.Set(0.5);
}
void SubClaw::OuttakeLeft(){
_spmLeftMotor.Set(-0.5);
}
void SubClaw::OuttakeRight(){
_spmRightMotor.Set(1);
}
void SubClaw::Stop(){
_spmLeftMotor.Set(0);
_spmRightMotor.Set(0);
}
