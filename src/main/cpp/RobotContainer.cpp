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
#include "subsystems/SubLED.h"
#include <frc/DriverStation.h>
#include "utilities/POVHelper.h"
#include <frc2/command/button/POVButton.h>

#include "subsystems/SubRollerIntake.h"


bool RobotContainer::isConeMode = true;

RobotContainer::RobotContainer() {
  // Initializing Subsystems
  SubArm::GetInstance();
  SubLED::GetInstance();
  SubRollerIntake::GetInstance();

  // Configure command bindings
  ConfigureBindings();
  SubDriveBase::GetInstance().SetDefaultCommand(CmdDriveRobot(&_driverController));

  _autoChooser.SetDefaultOption("Do Nothing", "DoNothing"); 
  _autoChooser.AddOption("PConeH", "PConeH");
  _autoChooser.AddOption("PConeH+C", "PConeH+C");
  _autoChooser.AddOption("PConeH+C_old", "PConeH+C_old");
  _autoChooser.AddOption("PConeH+Leave", "PConeH+Leave");
  _autoChooser.AddOption("PConeH+Leave+Hold(1)", "PConeH+Leave+Hold(1)");
  _autoChooser.AddOption("PConeH+Leave+Hold(3)", "PConeH+Leave+Hold(3)");
  _autoChooser.AddOption("Leave", "Leave");
  _autoChooser.AddOption("Climb", "Climb");


  frc::SmartDashboard::PutData("Auto Chooser", &_autoChooser);
}

void RobotContainer::ConfigureBindings() {
  using namespace frc2::cmd;

  //Main Controller
  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));
  _driverController.RightBumper().WhileTrue(cmd::RollerOuttake()); //outtake
  _driverController.RightTrigger().WhileTrue(cmd::RollerIntakeWithRumble(_driverController, _secondController));
  _driverController.LeftTrigger().OnTrue(cmd::ScoreSequence()); // score sequence

  //Second controller
  POVHelper::Up(&_secondController).WhileTrue(cmd::ManualArmMove(0, 20));
  POVHelper::Down(&_secondController).WhileTrue(cmd::ManualArmMove(0, -20)); //down
  POVHelper::Right(&_secondController).WhileTrue(cmd::ManualArmMove(20, 0)); //forward
  POVHelper::Left(&_secondController).WhileTrue(cmd::ManualArmMove(-20, 0)); //backward
  _secondController.Y().OnTrue(cmd::ArmToHigh());
  _secondController.B().OnTrue(cmd::ArmToMid());
  _secondController.A().OnTrue(cmd::ArmToLowCubeOrCone());
  _secondController.X().OnTrue(cmd::ArmPickUp());
  _secondController.LeftTrigger().OnTrue(cmd::ArmToLoadingStation());
  _secondController.RightTrigger().OnTrue(cmd::ArmToDefaultLocation());
  _secondController.LeftBumper().OnTrue(cmd::CubeConeSwitch());
  _secondController.RightBumper().WhileTrue(cmd::RollerOuttake());

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
  