// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"
#include <frc2/command/commands.h>
#include "subsystems/SubArm.h"
#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"
#include "commands/ArmCommands.h"

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
 
  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.

  /*
  _driverController.A().WhileTrue(cmd::Intake());
  _driverController.X().WhileTrue(cmd::Outtake());
  _driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  _driverController.LeftBumper().WhileTrue(cmd::ClawGrabCone());
  _driverController.RightTrigger().WhileTrue(cmd::ClawGrabCube());
  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();})); 
  */

/*
_driverController.A().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(0_deg, 0_deg);}));
_driverController.B().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(10_deg, 0_deg);}));
_driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(20_deg, 0_deg);}));
_driverController.Y().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(30_deg, 0_deg);}));
*/

_driverController.A().OnTrue(cmd::ArmToHigh());
_driverController.B().OnTrue(cmd::ArmToMid());
_driverController.LeftBumper().OnTrue(cmd::ArmToLowCubeOrCone());
_driverController.RightBumper().OnTrue(cmd::CubeConeSwitch());

// A = 1
// B = 2
// X = 3
// Y = 4
// LeftBumper = 5
// RightBumper = 6

}


