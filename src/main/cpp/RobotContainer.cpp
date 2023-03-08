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
#include "subsystems/SubLED.h"
#include "commands/CmdGridCommands.h"
#include <frc/DriverStation.h>
#include "utilities/POVHelper.h"
#include <frc2/command/button/POVButton.h>


bool RobotContainer::isConeMode = true;
grids::Grid RobotContainer::GridSelect = grids::Grid::Neutral;

RobotContainer::RobotContainer() {
  // Initializing Subsystems
  SubIntake::GetInstance();
  SubArm::GetInstance();
  SubClaw::GetInstance();
  SubLED::GetInstance();

  // Configure command bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));
  SubVision::GetInstance().SetDefaultCommand(cmd::AddVisionMeasurement());

  _autoChooser.SetDefaultOption("Do Nothing", "DoNothing"); 
  _autoChooser.AddOption("PreConeH+ScoreH(1)", "PreConeH+ScoreH(1)");   
  _autoChooser.AddOption("PreConeH+ScoreH(3)", "PreConeH+ScoreH(3)");   
  _autoChooser.AddOption("PreConeH", "PreConeH");   
  _autoChooser.AddOption("PreConeH+C", "PreConeH+C");
  _autoChooser.AddOption("PreConeH+1ho+C", "PreConeH+1ho+C");

  frc::SmartDashboard::PutData("Auto Chooser", &_autoChooser);
}

void RobotContainer::ConfigureBindings() {

  using namespace frc2::cmd;

  // Navx
  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));

  // Note: all arduino buttons are moved up 1 id, eg: in arduino ide, B4 is ID4, in VScode B4 is ID5
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
  //_driverController.X().WhileTrue(RunOnce([] {GridSelect = grids::Grid::LS;}).AndThen(cmd::Score(grids::Column::Left, grids::Height::LS)).AndThen(cmd::ClawExpand()));
  _driverController.B().WhileTrue(cmd::ArmToLoadingStation());

  // Arm
  _driverController.Y().OnTrue(cmd::ArmToHigh());
  //_driverController.B().OnTrue(cmd::ArmPickUp());
  _driverController.Back().OnTrue(cmd::DriveBottomArmToSwitch().AlongWith(cmd::DriveIntakeToSwitch()));
  POVHelper::Up(&_driverController).WhileTrue(cmd::ManualArmMove(0, 20));
  POVHelper::Down(&_driverController).WhileTrue(cmd::ManualArmMove(0, -20));
  POVHelper::Right(&_driverController).WhileTrue(cmd::ManualArmMove(20, 0)); //forward
  POVHelper::Left(&_driverController).WhileTrue(cmd::ManualArmMove(-20, 0)); //backward

  // Claw
  _driverController.RightBumper().OnTrue(cmd::StowGamePiece()); 
  _driverController.LeftBumper().OnTrue(cmd::CubeConeSwitch());
  _driverController.A().OnTrue(cmd::ClawToggle());
  _driverController.X().OnTrue(cmd::ClawIdle());
  
  // Intake
  _driverController.LeftTrigger().WhileTrue(cmd::Outtake());
  _driverController.RightTrigger().OnTrue(cmd::Intake());
  _driverController.RightTrigger().OnFalse(cmd::StopIntake());

  // Coast mode override toggle
  frc2::Trigger([&] {
    return frc::RobotController::GetUserButton() || _breakModeSwitch.Get();
  }).ToggleOnTrue(cmd::CoastModeOverride());
}



// For Auto Commands, removed temporarily
frc2::CommandPtr RobotContainer::GetAutonomousCommand() {
  _autoSelected = _autoChooser.GetSelected();
  return cmd::PPDrivePath(_autoSelected);
}
  