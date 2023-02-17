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
  SubClaw::GetInstance();

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
  
  //navx
  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));

//note: all arduino buttons are moved up 1 id, eg: in arduino ide, B4 is ID4, in VScode B4 is ID5
  _secondController.Button(4+1).WhileTrue(cmd::Score(grids::Column::Left, grids::Height::Low));
  _secondController.Button(5+1).WhileTrue(cmd::Score(grids::Column::Middle, grids::Height::Low));
  _secondController.Button(6+1).WhileTrue(cmd::Score(grids::Column::Right, grids::Height::Low));
  _secondController.Button(7+1).WhileTrue(cmd::Score(grids::Column::Left, grids::Height::Middle));
  _secondController.Button(8+1).WhileTrue(cmd::Score(grids::Column::Middle, grids::Height::Middle));
  _secondController.Button(9+1).WhileTrue(cmd::Score(grids::Column::Right, grids::Height::Middle));
  _secondController.Button(10+1).WhileTrue(cmd::Score(grids::Column::Left, grids::Height::High));
  _secondController.Button(11+1).WhileTrue(cmd::Score(grids::Column::Middle, grids::Height::High));
  _secondController.Button(12+1).WhileTrue(cmd::Score(grids::Column::Right, grids::Height::High));
  _secondController.Button(1+1).OnTrue(RunOnce([] {GridSelect = grids::Grid::Left;}));
  _secondController.Button(2+1).OnTrue(RunOnce([] {GridSelect = grids::Grid::Middle;}));
  _secondController.Button(3+1).OnTrue(RunOnce([] {GridSelect = grids::Grid::Right;}));
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
  return cmd::PPDrivePath("PreConeH");
}
