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
  m_driverController.A().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(20_deg, -20_deg);}));
  m_driverController.B().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(10_deg, 10_deg);}));
  //ARM_LENGTH = 1m, ARM_LENGTH_2 = 1m
  m_driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.17862_m + SubArm::ARM_ROOT_X, 0.07_m);})); //Cube/Cone low
  m_driverController.Y().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.222655_m + 0.35724_m + SubArm::ARM_ROOT_X, 0.67_m);})); //Cube mid
  //m_driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.2017795_m + 0.8024369_m + SubArm::ARM_ROOT_X, 0.97_m);})); //Cube high
  m_driverController.LeftBumper().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.559435_m + SubArm::ARM_ROOT_X, 0.862787_m + 0.07_m);})); //Cone mid
  m_driverController.RightBumper().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.99156774_m + SubArm::ARM_ROOT_X, 1.1668125_m + 0.07_m);})); //Cone high
}

frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return autos::ExampleAuto(&m_subsystem);
}
