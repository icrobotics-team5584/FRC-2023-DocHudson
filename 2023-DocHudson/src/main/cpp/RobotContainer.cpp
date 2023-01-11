// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"

#include <frc2/command/button/Trigger.h>
#include "subsystems/SubArm.h"
#include "commands/Autos.h"
#include "commands/ExampleCommand.h"
#include <frc2/command/Commands.h>

RobotContainer::RobotContainer() {
  // Initialize all of your commands and subsystems here
  SubArm::GetInstance();
  // Configure the button bindings
  ConfigureBindings();
}

void RobotContainer::ConfigureBindings() {
  using namespace frc2::cmd;
  // Configure your trigger bindings here

  // Schedule `ExampleCommand` when `exampleCondition` changes to `true`
  frc2::Trigger([this] {
    return m_subsystem.ExampleCondition();
  }).OnTrue(ExampleCommand(&m_subsystem).ToPtr());

  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  m_driverController.A().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(10_deg, 20_deg);}));
  m_driverController.B().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(40_deg, 60_deg);}));
  //ARM_LENGTH = 1m, ARM_LENGTH_2 = 1m
  m_driverController.LeftBumper().WhileTrue(Run([]{SubArm::GetInstance().ArmPos(1.3_m, 0.67_m);}));
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}
