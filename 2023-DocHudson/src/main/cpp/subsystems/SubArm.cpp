// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubArm.h"
#include <frc/smartdashboard/SmartDashboard.h>

SubArm::SubArm(){
    frc::SmartDashboard::PutData("Arm/Arm Motor 1: ", (wpi::Sendable*)&_armMotor1);

    _armMotor1.SetPIDFF(P, I, D, F);
    _armMotor1.ConfigSmartMotion(MAX_VEL, MAX_ACCEL, TOLERANCE);
    _armMotor1.SetConversionFactor(GEAR_RATIO);

}

// This method will be called once per scheduler run
void SubArm::Periodic(){}

void SubArm::SimulationPeriodic(){
    _armSim.SetInputVoltage(_armMotor1.GetSimVoltage());
    _armSim.Update(20_ms);

    auto armAngle = _armSim.GetAngle();
    auto armVel = _armSim.GetVelocity();
    _armMotor1.UpdateSimEncoder(armAngle, armVel);
}