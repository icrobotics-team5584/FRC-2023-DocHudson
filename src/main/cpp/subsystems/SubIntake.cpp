// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubIntake.h"
#include "RobotContainer.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/commands.h>
#include <frc2/command/button/Trigger.h>

SubIntake::SubIntake() {
  _leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
  _rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);

  frc::SmartDashboard::PutData("Intake/Deploy Motor: ", (wpi::Sendable*)&_deployMotor);
  _deployMotor.SetPIDFF(P, I, D, F);

/*
  frc2::Trigger([this] {
    return LocatingSwitchIsHit();
  }).OnTrue(frc2::cmd::RunOnce([this] {
              ZeroDeployMotor();
              _deployMotor.Set(0);
            }).IgnoringDisable(true));
*/
  _deployMotor.UseAbsoluteEncoder(_intakeEncoder);
}

// This method will be called once per scheduler run
void SubIntake::Periodic() {
  frc::SmartDashboard::PutNumber("Intake/Right side current", _rightMotor.GetOutputCurrent());
  frc::SmartDashboard::PutNumber("Intake/Right side duty cycle", _rightMotor.GetAppliedOutput());

  auto intakeErrorAngle = _intakeEncoder.GetPosition() * 360_deg - _deployMotor.GetPositionTarget();
  intakeErrorAngle = units::math::abs(intakeErrorAngle);

  if (_deployMotor.GetPositionTarget() == DEPLOY_POS && intakeErrorAngle < 5_deg) {
    _deployMotor.Set(0);
  }
}

void SubIntake::SimulationPeriodic() {
  _IntakeSim.SetInputVoltage(_deployMotor.GetSimVoltage());
  _IntakeSim.Update(20_ms);
  _deployMotor.UpdateSimEncoder(_IntakeSim.GetAngularPosition(),
                                _IntakeSim.GetAngularVelocity());
}

void SubIntake::DeployIntake() {
  _deployMotor.SetPositionTarget(DEPLOY_POS);
}

void SubIntake::RetractIntake() {
  _deployMotor.SetPositionTarget(STOWED_POS);
}

double SubIntake::GetIntakeSpeed() {
  return RobotContainer::isConeMode ? CONE_INTAKE_SPEED : CUBE_INTAKE_SPEED;
}

void SubIntake::IntakeLeft() {
  _leftMotor.Set(-GetIntakeSpeed());
}

void SubIntake::IntakeRight() {
  _rightMotor.Set(GetIntakeSpeed());
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

void SubIntake::ZeroDeployMotor() {
  _deployMotor.SetPosition(0_tr);
}

void SubIntake::DriveDeployMotor(double power) {
  _deployMotor.Set(power);
}

bool SubIntake::LocatingSwitchIsHit() {
  return _locatingSwitch.Get();
}

bool SubIntake::CheckReach() {
  auto intakeErrorAngle = _intakeEncoder.GetPosition() * 360_deg - _deployMotor.GetPositionTarget();
  intakeErrorAngle = units::math::abs(intakeErrorAngle);
  return intakeErrorAngle < 3_deg;
}