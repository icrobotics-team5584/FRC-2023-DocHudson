// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"

SubClaw::SubClaw() {
    frc::SmartDashboard::PutData("Claw/Claw Motor 1: ", (wpi::Sendable*)&_clawMotor1);

     _clawMotor1.SetPIDFF(P, I, D, F);

    _clawMotor1.SetPosition(0_tr);
     
}

// This method will be called once per scheduler run
void SubClaw::Periodic() {
    frc::SmartDashboard::PutNumber("claw Duty cycle", _clawMotor1.GetAppliedOutput());
    frc::SmartDashboard::PutNumber("claw Current", _clawMotor1.GetOutputCurrent());
    
//frc::SmartDashboard::PutNumber("RightClawPneumatc", _solPnuematicsLeft.Get());
//frc::SmartDashboard::PutNumber("LeftClawPneumatc", _solPnuematicsRight.Get());
}



void SubClaw::ClawClamped(){
    _clawMotor1.SetPositionTarget(0_tr);
}

void SubClaw::ClawUnclamped(){
    _clawMotor1.SetPositionTarget(18_tr);
}