// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>

#include "commands/Autos.h"
#include "commands/ExampleCommand.h"
#include "frc2/command/Commands.h"
#include "commands/CmdIntake.h"

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  SubClaw::GetInstance();

  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
    using BtnId = frc::XboxController::Button;
  using Btn = frc2::JoystickButton;
  // Configure your trigger bindings here
 //Btn{&_controller, BtnId::kA}.WhileHeld(CmdIntake{});
  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());



  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.B().WhileTrue(m_subsystem.ExampleMethodCommand());
  m_driverController.A().WhileTrue(CmdIntake().ToPtr());
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}
