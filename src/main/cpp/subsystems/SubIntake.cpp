// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"

#include <frc/smartdashboard/SmartDashboard.h>

SubIntake::SubIntake() {
  _leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  frc::SmartDashboard::PutData("Intake/Deploy Motor 1: ", (wpi::Sendable*)&_DeployMotor);
  _DeployMotor.SetPIDFF(P, I, D, F);
}

// This method will be called once per scheduler run
void SubIntake::Periodic() {
  frc::SmartDashboard::PutNumber("Intake/Right side current", _rightMotor.GetOutputCurrent());
  frc::SmartDashboard::PutNumber("Intake/Right side duty cycle", _rightMotor.GetAppliedOutput());

  if (_DeployMotor.GetPositionTarget() == DEPLOY_POS && _DeployMotor.GetPosError() < 5_deg) {
    _DeployMotor.Set(0);
  }
}

void SubIntake::SimulationPeriodic() {
  _IntakeSim.SetInputVoltage(_DeployMotor.GetSimVoltage());
  _IntakeSim.Update(20_ms);
  _DeployMotor.UpdateSimEncoder(_IntakeSim.GetAngularPosition(),
                                _IntakeSim.GetAngularVelocity());
}

void SubIntake::DeployIntake() {
  _DeployMotor.SetPositionTarget(DEPLOY_POS);
}

void SubIntake::RetractIntake() {
  _DeployMotor.SetPositionTarget(0_tr);
}

void SubIntake::IntakeLeft() {
  _leftMotor.Set(-0.3);
}

void SubIntake::IntakeRight() {
  _rightMotor.Set(0.3);
}

void SubIntake::OuttakeLeft() {
  _leftMotor.Set(1);
}

void SubIntake::OuttakeRight() {
  _rightMotor.Set(-1);
}

void SubIntake::Stop() {
  _leftMotor.Set(0);
  _rightMotor.Set(0);
}

bool SubIntake::SensesCone() {
  return _coneSensor.Get();
}
