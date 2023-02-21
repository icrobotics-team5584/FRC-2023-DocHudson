// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"

SubClaw::SubClaw() {
  frc::SmartDashboard::PutData("Claw/Claw Motor 1: ",
                               (wpi::Sendable*)&_clawMotor1);

  _clawMotor1.SetClosedLoopControlType(rev::CANSparkMax::ControlType::kPosition);
  _clawMotor1.SetPIDFF(P, I, D, F);

  _clawMotor1.UseAbsoluteEncoder(_clawEncoder);
  _clawMotor1.EnableSensorWrapping(0, 1);
  _clawMotor1.SetPosition(0_tr);
}

// This method will be called once per scheduler runte
void SubClaw::Periodic() {
  frc::SmartDashboard::PutNumber("Claw/Abs encoder pos", _clawEncoder.GetPosition());
  frc::SmartDashboard::PutNumber("Claw/current", _clawMotor1.GetOutputCurrent());
  frc::SmartDashboard::PutNumber("Claw/duty cycle", _clawMotor1.GetAppliedOutput());
}

void SubClaw::SimulationPeriodic() {
  _clawSim.SetInputVoltage(_clawMotor1.GetSimVoltage());
  _clawSim.Update(20_ms);
  _clawMotor1.UpdateSimEncoder(_clawSim.GetAngularPosition(),
                               _clawSim.GetAngularVelocity());
}

void SubClaw::ClawClampedCube() {
  _clawMotor1.SetPositionTarget(0.271152_tr);
}

void SubClaw::ClawClampedCone() {
  _clawMotor1.SetPositionTarget(0.397968_tr);
}

void SubClaw::ClawUnclamped() {
  _clawMotor1.SetPositionTarget(0.225265_tr);
}