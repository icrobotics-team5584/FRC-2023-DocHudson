// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include <frc2/command/commands.h>
#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"
#include "commands/AutoCommands.h"


RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  SubIntake::GetInstance();

  // Configure the button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_controller));
}

void RobotContainer::ConfigureBindings() {
  // Configure your trigger bindings here

  // pressed, cancelling on release.
  m_driverController.A().WhileTrue(CmdIntake().ToPtr());
  m_driverController.X().WhileTrue(CmdOuttake().ToPtr());
  m_driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
}

// For Auto Commands, removed temporarily
frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return cmd::PPDrivePath();
}

double RobotContainer::ControllerGetLeftX() {
  return _controller.GetLeftX();
}

double RobotContainer::ControllerGetLeftY() {
  return _controller.GetLeftY();
}

double RobotContainer::ControllerGetRightX() {
  return _controller.GetRightX();
}