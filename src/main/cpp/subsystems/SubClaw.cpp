// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"

SubClaw::SubClaw() = default;

// This method will be called once per scheduler run
void SubClaw::Periodic() {
//frc::SmartDashboard::PutNumber("RightClawPneumatc", _solPnuematicsLeft.Get());
//frc::SmartDashboard::PutNumber("LeftClawPneumatc", _solPnuematicsRight.Get());
}

void SubClaw::BothExtended(){
    _solPnuematicsLeft.Set(frc::DoubleSolenoid::Value::kForward);
    _solPnuematicsRight.Set(frc::DoubleSolenoid::Value::kForward);
}

void SubClaw::BothRetracted(){
    _solPnuematicsLeft.Set(frc::DoubleSolenoid::Value::kReverse);
    _solPnuematicsRight.Set(frc::DoubleSolenoid::Value::kReverse);
}

void SubClaw::OneExtended(){
    _solPnuematicsLeft.Set(frc::DoubleSolenoid::Value::kForward);
}
void SubClaw::OneRetracted(){
    _solPnuematicsRight.Set(frc::DoubleSolenoid::Value::kReverse);
}