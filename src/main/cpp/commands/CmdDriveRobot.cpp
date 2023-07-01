// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubArm.h"

CmdDriveRobot::CmdDriveRobot(frc::XboxController* controller) {
  _controller = controller;
  AddRequirements(&SubDriveBase::GetInstance());
}

// Called when the command is initially scheduled.
void CmdDriveRobot::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdDriveRobot::Execute() {
  const double deadband = 0.08;
  const auto xSpeed = -_xspeedLimiter.Calculate(frc::ApplyDeadband(_controller -> GetLeftY(), deadband)) * SubDriveBase::MAX_VELOCITY;
  const auto ySpeed = -_yspeedLimiter.Calculate(frc::ApplyDeadband(_controller -> GetLeftX(), deadband)) * SubDriveBase::MAX_VELOCITY;
  const auto rot = -_rotLimiter.Calculate(frc::ApplyDeadband(_controller -> GetRightX(), deadband)) * SubDriveBase::MAX_ANGULAR_VELOCITY;
  //SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, true);
  
  if (SubArm::GetInstance().GetEndEffectorTarget().Y() > 90_cm){SubDriveBase::GetInstance().Drive(xSpeed/2, ySpeed/2, rot/2, false);}
  // else if (_controller->GetLeftStickButton()){SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, false);}
  else {SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, true);} //true == field relative
}


// Called once the command ends or is interrupted.
void CmdDriveRobot::End(bool interrupted) {}

// Returns true when the command should end.
bool CmdDriveRobot::IsFinished() {
  return false;
}
