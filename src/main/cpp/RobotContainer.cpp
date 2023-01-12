// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"


RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  SubIntake::GetInstance();

  // Configure the button bindings
  ConfigureBindings();
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
}
