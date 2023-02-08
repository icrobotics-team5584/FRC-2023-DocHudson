// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include <frc2/command/button/Trigger.h>
#include <frc2/command/commands.h>
#include "commands/DriveCommands.h"
#include "subsystems/SubVision.h"
#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"
#include "commands/ArmCommands.h"
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"
#include "subsystems/SubArm.h"
#include "commands/AutoCommands.h"
bool RobotContainer::isConeMode = true;

RobotContainer::RobotContainer() {
  // Initializing Commmands
  SubIntake::GetInstance();
  SubArm::GetInstance();

  // Configure button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
  SubVision::GetInstance().SetDefaultCommand(cmd::AddVisionMeasurement());

  _autoChooser.SetDefaultOption("Do Nothing", "DoNothing"); 
  _autoChooser.AddOption("Get4m", "Get4m"); 

  frc::SmartDashboard::PutData("Auto Chooser", &_autoChooser);
}

void RobotContainer::ConfigureBindings() {

  using namespace frc2::cmd;
  
  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  _driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  _driverController.B().WhileTrue(cmd::LeftBumperExtend());
  _driverController.Y().WhileTrue(cmd::ArmToHigh());
  _driverController.X().WhileTrue(cmd::ArmToMid());
  _driverController.A().WhileTrue(cmd::ArmPickUp());
  _driverController.LeftBumper().WhileTrue(cmd::Intake());
  _driverController.RightBumper().WhileTrue(cmd::Outtake());
  _driverController.LeftTrigger().WhileTrue(cmd::BothBumperExtend());

  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
  _driverController.Back().OnTrue(frc2::cmd::RunOnce([]{SubArm::GetInstance().ArmResettingPos();}).IgnoringDisable(true));
  //_driverController.B().WhileTrue(cmd::AddVisionMeasurement());

//note: all arduino buttons are moved up 1 id, eg: in arduino ide, B4 is ID4, in VScode B4 is ID5
  _secondController.Button(5).WhileTrue(frc2::cmd::Print("ArduinoButton5"));
  _secondController.Button(6).WhileTrue(frc2::cmd::Print("ArduinoButton6"));
}

// For Auto Commands, removed temporarily
frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return cmd::PPDrivePath("PreConeH+C");
}