#pragma once

#include <frc2/command/commands.h>
namespace cmd {
frc2::CommandPtr StowGamePiece();

frc2::CommandPtr RollerIntake();
frc2::CommandPtr RollerOuttake();
frc2::CommandPtr IdleRollerIntake();

frc2::CommandPtr StartRollerIntake();
frc2::CommandPtr StartRollerOuttake();
frc2::CommandPtr StopRollerIntake();
frc2::CommandPtr StopRollerOuttake();
frc2::CommandPtr ShootCube();
}