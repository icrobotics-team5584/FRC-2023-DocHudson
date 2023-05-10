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


bool RobotContainer::isConeMode = true;

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
  _autoChooser.AddOption("PreConeH", "PreConeH");   
  _autoChooser.AddOption("PreConeH+C", "PreConeH+C");
  _autoChooser.AddOption("PreConeH+1ho+C", "PreConeH+1ho+C");
  _autoChooser.AddOption("PreConeH+Leave", "PreConeH+Leave");



  frc::SmartDashboard::PutData("Auto Chooser", &_autoChooser);
}

void RobotContainer::ConfigureBindings() {

  using namespace frc2::cmd;

  //Main Controller

  _driverController.Start().OnTrue(frc2::cmd::RunOnce([]{SubDriveBase::GetInstance().ResetGyroHeading();}));

  _driverController.Back().OnTrue(cmd::DriveBottomArmToSwitch().AlongWith(cmd::DriveIntakeToSwitch()));

  POVHelper::Up(&_secondController).WhileTrue(cmd::ManualArmMove(0, 20));
  POVHelper::Down(&_secondController).WhileTrue(cmd::ManualArmMove(0, -20));
  POVHelper::Right(&_secondController).WhileTrue(cmd::ManualArmMove(20, 0)); //forward
  POVHelper::Left(&_secondController).WhileTrue(cmd::ManualArmMove(-20, 0)); //backward

  _driverController.A().OnTrue(cmd::ClawToggle());  //Change to new end effector on
  _driverController.X().OnTrue(cmd::ClawIdle());    //Change to new end effector off
  _driverController.Y().OnTrue(frc2::cmd::RunOnce([]{SubArm::GetInstance().ArmResettingPos();}));
  
  _driverController.LeftTrigger().WhileTrue(cmd::Outtake());  
  _driverController.RightTrigger().OnTrue(cmd::Intake());
  _driverController.RightTrigger().OnFalse(cmd::StopIntake());




  //Second controller
  _secondController.Y().OnTrue(cmd::ArmToHigh());
  _secondController.B().OnTrue(cmd::ArmToMid());
  _secondController.A().OnTrue(cmd::ArmToLowCubeOrCone());
  _secondController.X().OnTrue(cmd::ArmPickUp());
  _secondController.LeftTrigger().OnTrue(cmd::ArmToLoadingStation());
  _secondController.RightTrigger().OnTrue(cmd::StowGamePiece());
  _secondController.RightBumper().OnTrue(cmd::CubeConeSwitch());


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
  