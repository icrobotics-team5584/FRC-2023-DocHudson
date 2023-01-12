#pragma once

#include <frc2/command/commands.h>

namespace cmd {
frc2::CommandPtr ClawGrabCone();
frc2::CommandPtr ClawGrabCube();
frc2::CommandPtr ClawExpand();
frc2::CommandPtr Intake();
frc2::CommandPtr Outtake();
}