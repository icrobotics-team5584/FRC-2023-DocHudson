#pragma once

#include <frc2/command/commands.h>

namespace cmd {
frc2::CommandPtr Intake();
frc2::CommandPtr Outtake();
frc2::CommandPtr ClawOpen();
frc2::CommandPtr ClawClose();
}