// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubClaw::SubClaw() {
    _spmIntake.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    _spmIntake.SetSmartCurrentLimit(20);
    frc::SmartDashboard::PutData("Claw/motor", (wpi::Sendable*)&_spmIntake);
}

// This method will be called once per scheduler run
void SubClaw::Periodic() {
   
}
void SubClaw::Intake(){
_spmIntake.Set(-1);
}
void SubClaw::Stop(){
_spmIntake.Set(0);
}