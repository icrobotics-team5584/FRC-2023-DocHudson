// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"

SubClaw::SubClaw() {
    frc::SmartDashboard::PutData("Claw/Claw Motor 1: ", (wpi::Sendable*)&_clawMotor1);

     _clawMotor1.SetPIDFF(P, I, D, F);

    _clawMotor1.UseAbsoluteEncoder(_clawEncoder);

    _clawMotor1.SetPosition(0_tr);
     
}

// This method will be called once per scheduler run
void SubClaw::Periodic() {
    frc::SmartDashboard::PutNumber("claw Duty cycle", _clawMotor1.GetAppliedOutput());
    frc::SmartDashboard::PutNumber("claw Current", _clawMotor1.GetOutputCurrent());
}



void SubClaw::ClawClampedCube(){
    _clawMotor1.SetPositionTarget(30_deg);
}

void SubClaw::ClawClampedCone(){
    _clawMotor1.SetPositionTarget(15_deg);
}

void SubClaw::ClawUnclamped(){
    _clawMotor1.SetPositionTarget(45_deg);
}