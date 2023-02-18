// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"

SubClaw::SubClaw() {
    frc::SmartDashboard::PutData("Claw/Claw Motor 1: ", (wpi::Sendable*)&_clawMotor1);

     _clawMotor1.SetPIDFF(P, I, D, F);

    _clawMotor1.UseAbsoluteEncoder(_clawEncoder);
     
}

// This method will be called once per scheduler runte
void SubClaw::Periodic() {
    frc::SmartDashboard::PutNumber("Claw/claw Duty cycle", _clawMotor1.GetAppliedOutput());
    frc::SmartDashboard::PutNumber("Claw/claw Current", _clawMotor1.GetOutputCurrent());
    frc::SmartDashboard::PutNumber("Claw/power", _clawMotor1.GetSimVoltage().value());
    frc::SmartDashboard::PutNumber("Claw/Encoder Pos", _clawEncoder.GetPosition());
    
//frc::SmartDashboard::PutNumber("RightClawPneumatc", _solPnuematicsLeft.Get());
//frc::SmartDashboard::PutNumber("LeftClawPneumatc", _solPnuematicsRight.Get());
}

void SubClaw::SimulationPeriodic() {
    _clawSim.SetInputVoltage(_clawMotor1.GetSimVoltage());
    _clawSim.Update(20_ms);
    _clawMotor1.UpdateSimEncoder(_clawSim.GetAngularPosition(), _clawSim.GetAngularVelocity());
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