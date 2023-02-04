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
#include "commands/AutoCommands.h"
#include "commands/CmdGridCommands.h"


bool RobotContainer::isConeMode = true;
grids::Grid RobotContainer::GridSelect = grids::Grid::Neutral;

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
  // _driverController.Y().WhileTrue(cmd::ArmToHigh());
  // _driverController.Y().WhileTrue(cmd::ArmPickUp());
  _driverController.Y().WhileTrue(Run([]{SubDriveBase::GetInstance().DriveToPose(frc::Pose2d{1_m, 1_m, 0_deg});}));
  _driverController.X().WhileTrue(RunOnce([]{SubDriveBase::GetInstance().SetPose(frc::Pose2d{0_m, 0_m, 0_deg});}));
  _driverController.LeftBumper().WhileTrue(cmd::Intake());
  _driverController.RightBumper().WhileTrue(cmd::Outtake());
  _driverController.LeftTrigger().WhileTrue(cmd::BothBumperExtend());

  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
  //_driverController.B().WhileTrue(cmd::AddVisionMeasurement());

//note: all arduino buttons are moved up 1 id, eg: in arduino ide, B4 is ID4, in VScode B4 is ID5
  _secondController.Button(5).WhileTrue(cmd::Score(grids::Column::Right, grids::Height::High));
  _secondController.Button(6).WhileTrue(frc2::cmd::Print("ArduinoButton6"));
  _secondController.Button(14).OnTrue(RunOnce([] {GridSelect = grids::Grid::Left;}));
  _secondController.Button(13).OnTrue(RunOnce([] {GridSelect = grids::Grid::Middle;}));
  _secondController.Button(12).OnTrue(RunOnce([] {GridSelect = grids::Grid::Right;}));
}
  


// For Auto Commands, removed temporarily
frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  return cmd::PPDrivePath("1PreloadScore+Climb");
}
