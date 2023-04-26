#pragma once

#include <frc2/command/commands.h>

namespace cmd {
frc2::CommandPtr ClawGrabCone();
frc2::CommandPtr ClawGrabCube();
frc2::CommandPtr ClawToggle();
frc2::CommandPtr ClawExpand();
frc2::CommandPtr Intake();
frc2::CommandPtr StartIntake();
frc2::CommandPtr StopIntake();
frc2::CommandPtr Outtake();
frc2::CommandPtr StartOuttake();
frc2::CommandPtr StopOuttake();
frc2::CommandPtr ClawClose();
frc2::CommandPtr StowGamePiece();
frc2::CommandPtr DeployIntake();
frc2::CommandPtr DriveIntakeToSwitch();
frc2::CommandPtr ClawIdle();

frc2::CommandPtr RollerIntake();
frc2::CommandPtr RollerOuttake();
frc2::CommandPtr IdleRollerIntake();
}