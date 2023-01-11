// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Command.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/XboxController.h>
#include <frc2/command/InstantCommand.h>

#include "Constants.h"
#include "subsystems/SubIntake.h"
#include "commands/CmdOuttake.h"
#include "commands/CmdIntake.h"
#include "utilities/JoystickScaler.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and trigger mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();
  double ControllerGetLeftX();
  double ControllerGetLeftY();
  double ControllerGetRightX();
  frc2::CommandPtr GetAutonomousCommand();

 private:
  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController m_driverController{0};
  
  void ConfigureBindings();
  JoystickScaler _controller {0, 2.5, 2.5};
};
