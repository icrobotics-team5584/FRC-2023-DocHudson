// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"

CmdDriveRobot::CmdDriveRobot(frc::XboxController* controller) {
  // Use addRequirements() here to declare subsystem dependencies.
  _controller = controller;
  AddRequirements(&SubDriveBase::GetInstance());
}

// Called when the command is initially scheduled.
void CmdDriveRobot::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDriveRobot::Execute() {
  const double deadband = 0.17;
  const auto xSpeed = -_xspeedLimiter.Calculate(frc::ApplyDeadband(_controller -> GetLeftY(), deadband)) * SubDriveBase::MAX_VELOCITY;
  const auto ySpeed = -_yspeedLimiter.Calculate(frc::ApplyDeadband(_controller -> GetLeftX(), deadband)) * SubDriveBase::MAX_VELOCITY;
  const auto rot = -_rotLimiter.Calculate(frc::ApplyDeadband(_controller -> GetRightX(), deadband)) * SubDriveBase::MAX_ANGULAR_VELOCITY;
  SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, true);
}

// Called once the command ends or is interrupted.
void CmdDriveRobot::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdDriveRobot::IsFinished() {
  return false;
}
