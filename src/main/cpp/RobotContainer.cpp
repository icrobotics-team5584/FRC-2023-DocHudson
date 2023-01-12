// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"
#include <frc2/command/commands.h>

#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"


RobotContainer::RobotContainer() {
  // Initializing Commmands
  SubIntake::GetInstance();

  // Configure button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_controller));
}

void RobotContainer::ConfigureBindings() {
    //using BtnId = frc::XboxController::Button;
   // using Btn = frc2::JoystickButton;
 
  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.A().WhileTrue(cmd::Intake());
  m_driverController.X().WhileTrue(cmd::Outtake());
  m_driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  m_driverController.LeftBumper().WhileTrue(cmd::ClawGrabCone());
  m_driverController.RightTrigger().WhileTrue(cmd::ClawGrabCube());


  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
}
