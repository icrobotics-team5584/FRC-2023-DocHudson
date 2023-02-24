// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

// Libraries includes
#include <frc2/command/Command.h>
#include <frc2/command/button/CommandXboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/button/CommandGenericHID.h> 
#include <frc2/command/InstantCommand.h>
#include <frc/XboxController.h>
#include <frc/smartdashboard/SendableChooser.h>

// Created classes includes 
#include "Constants.h"
#include "subsystems/SubIntake.h"
#include <frc/XboxController.h>
#include <frc2/command/button/CommandGenericHID.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/SubClaw.h"
#include "subsystems/SubIntake.h"
#include "utilities/Grids.h"
#include <frc/DigitalInput.h>



class RobotContainer {
 public:
  RobotContainer();
  double ControllerGetLeftX();
  double ControllerGetLeftY();
  double ControllerGetRightX();
  frc2::CommandPtr GetAutonomousCommand();

  static bool isConeMode;
  static grids::Grid GridSelect;

 private:
  // Replace with CommandPS4Controller or CommandJoystick if needed
  frc2::CommandXboxController _driverController{0};
  frc2::CommandGenericHID _secondController{1};

  frc::DigitalInput _breakModeSwitch{dio::breakModeSwitch};
  
  void ConfigureBindings();
  void SetConeMode();
  void SetCubeMode();
  
  frc::SendableChooser<std::string> _autoChooser;
};
