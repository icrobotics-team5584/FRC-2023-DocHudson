#pragma once

#include <frc2/command/commands.h>
#include "utilities/Grids.h"

namespace cmd {

    frc2::CommandPtr ArmToHighCube();
    frc2::CommandPtr ArmToMidCube();
    frc2::CommandPtr ArmToHighCone();
    frc2::CommandPtr ArmToMidCone();
    frc2::CommandPtr ArmToScoringHeight(grids::Height height);

    frc2::CommandPtr ArmToLoadingStation();
    frc2::CommandPtr ArmToLowCubeOrCone();
    frc2::CommandPtr ArmToDefaultLocation();

    frc2::CommandPtr CubeConeSwitch();
    frc2::CommandPtr ArmToHigh();
    frc2::CommandPtr ArmToMid();

    frc2::CommandPtr ArmPickUp(); 
    frc2::CommandPtr PickUpCube();
    frc2::CommandPtr PickUpCone();
    frc2::CommandPtr PickUpUprightCone();
    frc2::CommandPtr PickUpSlantedCone();

    frc2::CommandPtr ArmToPos(auto x, auto y);
}