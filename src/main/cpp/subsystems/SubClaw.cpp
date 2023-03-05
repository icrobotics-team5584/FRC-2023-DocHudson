// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubClaw.h"
#include <frc2/command/commands.h>
#include <frc2/command/button/Trigger.h>

SubClaw::SubClaw() {
  frc::SmartDashboard::PutData("Claw/Claw Motor 1: ",
                               (wpi::Sendable*)&_clawMotor1);

  _clawMotor1.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  _clawMotor1.SetClosedLoopControlType(
      rev::CANSparkMax::ControlType::kPosition);
  _clawMotor1.SetPIDFF(P, I, D, F);

  // uncomment me to use absolute encoder
  //_clawMotor1.UseAbsoluteEncoder(_clawEncoder);
  //_clawMotor1.EnableSensorWrapping(0, 1);

  frc2::Trigger([this] {
    return OnClampedSwitch();
  }).OnTrue(frc2::cmd::RunOnce([this] {
              LocateClawOnSwitch();
              Stop();
            }).IgnoringDisable(true));
}

// This method will be called once per scheduler runte
void SubClaw::Periodic() {
  frc::SmartDashboard::PutNumber("Claw/current",
                                 _clawMotor1.GetOutputCurrent());
  frc::SmartDashboard::PutNumber("Claw/duty cycle",
                                 _clawMotor1.GetAppliedOutput());
  frc::SmartDashboard::PutNumber("Claw/is trying to unclamp", IsTryingToUnclamp());
  frc::SmartDashboard::PutNumber("Claw/Clamp Switch", OnClampedSwitch());
  frc::SmartDashboard::PutNumber("Claw/Unclamp Switch", OnUnClampedSwitch());

  // uncomment me to use absolute encoder
  // frc::SmartDashboard::PutNumber("Claw/Abs encoder pos",
  // _clawEncoder.GetPosition());
}

void SubClaw::SimulationPeriodic() {
  _clawSim.SetInputVoltage(_clawMotor1.GetSimVoltage());
  _clawSim.Update(20_ms);
  _clawMotor1.UpdateSimEncoder(_clawSim.GetAngularPosition(),
                               _clawSim.GetAngularVelocity());
}

void SubClaw::ClawClampedCube() {
  _clawMotor1.SetPositionTarget(CUBE_CLAMPED_POS);
  _isTryingToUnclamp = false;
}

void SubClaw::ClawClampedCone() {
  _clawMotor1.Set(0.5);
  _isTryingToUnclamp = false;
}

void SubClaw::ClawUnclamped() {
  _clawMotor1.Set(-0.4);
  _isTryingToUnclamp = true;
}

bool SubClaw::IsTryingToUnclamp() {
  return _isTryingToUnclamp;
}

void SubClaw::LocateClawOnSwitch() {
  _clawMotor1.SetPosition(0_tr);
}

bool SubClaw::OnClampedSwitch() {
  return !_clawClampedSwitch.Get();
}

bool SubClaw::OnUnClampedSwitch() {
  return !_clawUnclampedSwitch.Get();
}

void SubClaw::Stop() {
  _clawMotor1.Set(0);
}