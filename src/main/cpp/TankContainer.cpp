#include "TankContainer.h"
#include "subsystems/SubTankDrive.h"
#include "commands/CmdDriveRobotTank.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "RobotContainer.h"
#include <frc2/command/button/Trigger.h>
#include "frc2/command/Commands.h"
#include "commands/GamePieceCommands.h"
#include <frc2/command/commands.h>
#include "commands/CmdDriveRobot.h"
#include "subsystems/SubDriveBase.h"

TankContainer::TankContainer(){
  // Initialize all of your commands and subsystems here
  SubTankDrive::GetInstance().SetDefaultCommand(CmdDriveRobotTank{&_driverController});
  // Configure the button bindings
  ConfigureButtonBindings();
  
	// Disable Swerve shown on dashboard
//   frc::SmartDashboard::PutBoolean("SwerveDrive Enabled", false);

}

void TankContainer::ConfigureButtonBindings() {
 _secondController.Button(5).WhileTrue(cmd::Intake());
  _secondController.Button(6).WhileTrue(cmd::Outtake());
  _driverController.RightBumper().WhileTrue(cmd::ClawExpand());
  _driverController.LeftBumper().WhileTrue(cmd::ClawGrabCone());
  _driverController.RightTrigger().WhileTrue(cmd::ClawGrabCube());
  _driverController.B().WhileTrue(cmd::LeftBumperExtend());
  _driverController.Y().WhileTrue(cmd::RightBumperExtend());
  _driverController.Back().WhileTrue(cmd::BothBumperExtend());
}

frc2::Command* TankContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}