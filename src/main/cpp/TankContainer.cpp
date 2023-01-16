#include "TankContainer.h"
#include "subsystems/SubTankDrive.h"
#include "commands/CmdDriveRobotTank.h"
#include <frc/smartdashboard/SmartDashboard.h>

TankContainer::TankContainer(){
  // Initialize all of your commands and subsystems here
  SubTankDrive::GetInstance().SetDefaultCommand(CmdDriveRobotTank{&_controller});
  // Configure the button bindings
  ConfigureButtonBindings();
  
	// Disable Swerve shown on dashboard
//   frc::SmartDashboard::PutBoolean("SwerveDrive Enabled", false);

}

void TankContainer::ConfigureButtonBindings() {
}

frc2::Command* TankContainer::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return nullptr;
}
