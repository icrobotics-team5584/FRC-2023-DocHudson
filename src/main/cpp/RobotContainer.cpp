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


RobotContainer::RobotContainer() {
  // Initializing Commmands
  SubIntake::GetInstance();

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

  _driverController.A().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(20_deg, -20_deg);}));
  _driverController.B().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(10_deg, 10_deg);}));
  //ARM_LENGTH = 1m, ARM_LENGTH_2 = 1m
  _driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.17862_m + SubArm::ARM_ROOT_X, 0.07_m);})); //Cube/Cone low
  _driverController.Y().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.222655_m + 0.35724_m + SubArm::ARM_ROOT_X, 0.67_m);})); //Cube mid
  //_driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.2017795_m + 0.8024369_m + SubArm::ARM_ROOT_X, 0.97_m);})); //Cube high
  _driverController.LeftBumper().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.559435_m + SubArm::ARM_ROOT_X, 0.97_m);})); //Cone mid
  _driverController.RightBumper().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.99156774_m + SubArm::ARM_ROOT_X, 1.1668125_m + 0.07_m);})); //Cone high

}

