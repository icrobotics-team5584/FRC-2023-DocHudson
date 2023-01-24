#pragma once

#include <frc2/command/commands.h>

namespace cmd {
frc2::CommandPtr ClawGrabCone();
frc2::CommandPtr ClawGrabCube();
frc2::CommandPtr ClawExpand();
frc2::CommandPtr Intake();
frc2::CommandPtr Outtake();
frc2::CommandPtr ClawReleaseCone();
frc2::CommandPtr ClawReleaseCube();
frc2::CommandPtr RightBumperExtend();
frc2::CommandPtr LeftBumperExtend();
frc2::CommandPtr BothBumperExtend();
}