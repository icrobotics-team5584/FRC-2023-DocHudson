// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/button/Trigger.h>
#include <frc2/command/commands.h>
#include "subsystems/SubArm.h"
#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"
#include "commands/ArmCommands.h"
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"

bool RobotContainer::isConeMode = true;

RobotContainer::RobotContainer() {
  // Initializing Commmands
  SubIntake::GetInstance();
  SubArm::GetInstance();

  // Configure button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));  
}

void RobotContainer::ConfigureBindings() {
  using namespace frc2::cmd;

  /*
  _driverController.A().WhileTrue(cmd::Intake());
  _driverController.X().WhileTrue(cmd::Outtake());
  _driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  _driverController.LeftBumper().WhileTrue(cmd::ClawGrabCone());
  _driverController.RightTrigger().WhileTrue(cmd::ClawGrabCube());
  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();})); 
  */

_driverController.A().OnTrue(cmd::ArmToHigh());
_driverController.B().OnTrue(cmd::ArmToMid());
_driverController.X().OnTrue(cmd::PickUpUprightCone()); 
_driverController.Y().OnTrue(cmd::PickUpCube());
_driverController.LeftBumper().OnTrue(cmd::ArmToLowCubeOrCone());
_driverController.RightBumper().OnTrue(cmd::CubeConeSwitch());
_driverController.Start().OnTrue(cmd::ArmToDefaultLocation());
_driverController.Back().OnTrue(RunOnce([]{SubArm::GetInstance().ArmResettingPos();}));

// A = 1
// B = 2
// X = 3
// Y = 4
// LeftBumper = 5
// RightBumper = 6
// Back = 7
// Start = 8

}
