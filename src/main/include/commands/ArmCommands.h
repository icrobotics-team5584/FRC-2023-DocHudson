#pragma once

#include <frc2/command/commands.h>

namespace cmd {
    frc2::CommandPtr ArmToHighCube();
    frc2::CommandPtr ArmToMidCube();

    frc2::CommandPtr ArmToHighCone();
    frc2::CommandPtr ArmToMidCone();

    frc2::CommandPtr ArmToLoadingStation();
    frc2::CommandPtr ArmToLowCubeOrCone();

    frc2::CommandPtr CubeConeSwitch();
    
    frc2::CommandPtr ArmToHigh();
    frc2::CommandPtr ArmToMid();

}