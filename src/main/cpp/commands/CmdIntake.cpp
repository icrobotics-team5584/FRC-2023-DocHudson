// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdIntake.h"

CmdIntake::CmdIntake() {
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void CmdIntake::Initialize() {
 

}

// Called repeatedly when this Command is scheduled to run
void CmdIntake::Execute() {
   SubClaw::GetInstance().IntakeLeft();
   SubClaw::GetInstance().IntakeRight();
   
}

// Called once the command ends or is interrupted.
void CmdIntake::End(bool interrupted) {
  SubClaw::GetInstance().Stop();
}

// Returns true when the command should end.
bool CmdIntake::IsFinished() {
  return false;
}
