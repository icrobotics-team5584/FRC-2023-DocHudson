#pragma once

#include <frc2/command/commands.h>

namespace cmd {
frc2::CommandPtr ClawGrabCone();
frc2::CommandPtr ClawGrabCube();
frc2::CommandPtr ClawExpand();
frc2::CommandPtr ClawRetract();
frc2::CommandPtr Intake();
frc2::CommandPtr StartIntake();
frc2::CommandPtr StopIntake();
frc2::CommandPtr Outtake();
frc2::CommandPtr ClawReleaseCone();
frc2::CommandPtr ClawReleaseCube();
frc2::CommandPtr StartOuttake();
frc2::CommandPtr StopOuttake();
frc2::CommandPtr RightBumperExtend();
frc2::CommandPtr LeftBumperExtend();
frc2::CommandPtr BothBumperExtend();
frc2::CommandPtr ClawOpen();
frc2::CommandPtr ClawClose();
}