// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdOuttake.h"
#include "subsystems/SubIntake.h"

CmdOuttake::CmdOuttake() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void CmdOuttake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void CmdOuttake::Execute() {
  SubIntake::GetInstance().OuttakeLeft();
  SubIntake::GetInstance().OuttakeRight();
}

// Called once the command ends or is interrupted.
void CmdOuttake::End(bool interrupted) {
  SubIntake::GetInstance().Stop();
}

// Returns true when the command should end.
bool CmdOuttake::IsFinished() {
  return false;
}
