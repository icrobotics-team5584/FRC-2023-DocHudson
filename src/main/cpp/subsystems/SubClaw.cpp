// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubClaw::SubClaw() {
    _spmIntake.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    _spmOuttake.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

    _spmIntake.SetSmartCurrentLimit(20);
    _spmOuttake.SetSmartCurrentLimit(20);

    frc::SmartDashboard::PutData("Claw/IntakeMotor", (wpi::Sendable*)&_spmIntake);
    frc::SmartDashboard::PutData("Claw/OuttakeMotor", (wpi::Sendable*)&_spmOuttake);
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
void SubClaw::Outtake(){
_spmOuttake.Set(1);
}