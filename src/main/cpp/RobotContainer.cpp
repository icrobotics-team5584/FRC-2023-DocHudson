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
  SubClaw::GetInstance();

  // Configure button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
  SubVision::GetInstance().SetDefaultCommand(cmd::AddVisionMeasurement());
}

void RobotContainer::ConfigureBindings() {

  using namespace frc2::cmd;
  
  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.


  //navx
  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));

  //arm
  _driverController.Y().OnTrue(cmd::ArmToHigh());
  _driverController.B().OnTrue(cmd::ArmToLowCubeOrCone());

  _driverController.Back().OnTrue(frc2::cmd::RunOnce([]{SubArm::GetInstance().ArmResettingPos();}).IgnoringDisable(true));
  
  //claw
   _driverController.RightBumper().WhileTrue(cmd::ClawClose()); //Should do --> picks up whatever is in intake and brings everything back into robot
   _driverController.LeftBumper().OnTrue(cmd::CubeConeSwitch());
   _driverController.A().OnTrue(cmd::ClawOpen());
   //_driverController.A().OnTrue(isConeMode = False);
   
   
  //intake
   _driverController.LeftTrigger().WhileTrue(cmd::Outtake());
   _driverController.RightTrigger().WhileTrue(cmd::Intake());
  
  //arduino
  //note: all arduino buttons are moved up 1 id, eg: in arduino ide, B4 is ID4, in VScode B4 is ID5
}

// For Auto Commands, removed temporarily
frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return cmd::PPDrivePath("TestRotation");
}