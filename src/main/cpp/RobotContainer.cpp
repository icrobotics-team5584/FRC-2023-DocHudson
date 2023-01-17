// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"
#include <frc2/command/commands.h>

#include "commands/DriveCommands.h"

#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"
#include "frc/DataLogManager.h"


RobotContainer::RobotContainer() {
  frc::DataLogManager::Start();
  // Initializing Commmands
  SubIntake::GetInstance();

  // Configure button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
}

void RobotContainer::ConfigureBindings() {
    //using BtnId = frc::XboxController::Button;
   // using Btn = frc2::JoystickButton;
 
  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  _driverController.A().WhileTrue(cmd::Intake());
  _driverController.X().WhileTrue(cmd::Outtake());
  _driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  _driverController.LeftBumper().WhileTrue(cmd::ClawGrabCone());
  _driverController.RightTrigger().WhileTrue(cmd::ClawGrabCube());
  _driverController.B().WhileTrue(cmd::LeftBumperExtend());
  _driverController.Y().WhileTrue(cmd::RightBumperExtend());
  _driverController.LeftTrigger().WhileTrue(cmd::BothBumperExtend());


  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
  _driverController.B().WhileTrue(cmd::AddVisionMeasurement());
}
