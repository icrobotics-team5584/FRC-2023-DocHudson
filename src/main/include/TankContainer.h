#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/InstantCommand.h>
#include "Utilities/JoystickScaler.h"

class TankContainer {
 public:
  TankContainer();
  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...
  void ConfigureButtonBindings();
  JoystickScaler _controller {0, 2.5, 2.5};
};