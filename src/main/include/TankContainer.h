#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/InstantCommand.h>
#include "Utilities/JoystickScaler.h"
#include "subsystems/SubIntake.h"
#include "subsystems/SubClaw.h"
#include "Constants.h"
#include <frc2/command/button/CommandXboxController.h>






class TankContainer {
 public:
  TankContainer();
  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  void ConfigureButtonBindings();
  //JoystickScaler _controller {0, 2.5, 2.5};
   frc2::CommandXboxController _driverController{0};
};