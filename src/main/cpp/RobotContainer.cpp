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
#include "utilities/Grids.h"



bool RobotContainer::isConeMode = true;
grids::Grid RobotContainer::GridSelect = Grid::Neutral;

RobotContainer::RobotContainer() {
  // Initializing Commmands
  SubIntake::GetInstance();
  SubArm::GetInstance();

  // Configure button bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
  SubVision::GetInstance().SetDefaultCommand(cmd::AddVisionMeasurement());
}

void RobotContainer::ConfigureBindings() {

  using namespace frc2::cmd;
  
  // Schedule `ExampleMethodCommand` when the Xbox controller's B button is
  // pressed, cancelling on release.
  
  // _driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  //_driverController.LeftBumper().WhileTrue(cmd::ClawGrabCone());
  //_driverController.RightTrigger().WhileTrue(cmd::ClawGrabCube());
  //_driverController.B().WhileTrue(cmd::LeftBumperExtend());
  //_driverController.Y().WhileTrue(cmd::RightBumperExtend());
  //_driverController.LeftTrigger().WhileTrue(cmd::BothBumperExtend());
  

_driverController.A().OnTrue(cmd::ArmToHigh());
_driverController.B().OnTrue(cmd::ArmToMid());
_driverController.X().OnTrue(cmd::ArmPickUp()); 
_driverController.Y().OnTrue(cmd::PickUpCube());
_driverController.LeftBumper().OnTrue(cmd::ArmToLowCubeOrCone());
_driverController.RightBumper().OnTrue(cmd::CubeConeSwitch());
_driverController.Start().OnTrue(cmd::ArmToLoadingStation());
_driverController.Back().OnTrue(RunOnce([]{SubArm::GetInstance().ArmResettingPos();}));

// A = 1 | LeftBumper = 5
// B = 2 | RightBumper = 6
// X = 3 | Back = 7
// Y = 4 | Start = 8

//  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
//  _driverController.B().WhileTrue(cmd::AddVisionMeasurement());

//note: all arduino buttons are moved up 1 id, eg: in arduino ide, B4 is ID4, in VScode B4 is ID5
  _secondController.Button(5).WhileTrue(frc2::cmd::Print("ArduinoButton5"));
  _secondController.Button(6).WhileTrue(frc2::cmd::Print("ArduinoButton6"));
  _secondController.Button(14).OnTrue(RunOnce([] {GridSelect = Left;}));
  _secondController.Button(13).OnTrue(RunOnce([] {GridSelect = Middle;}));
  _secondController.Button(12).OnTrue(RunOnce([] {GridSelect = Right;}));
  
}
