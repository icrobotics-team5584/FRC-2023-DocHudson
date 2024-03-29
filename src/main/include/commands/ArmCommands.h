#pragma once

#include <frc2/command/commands.h>

namespace cmd {

    frc2::CommandPtr ArmToHighCube();
    frc2::CommandPtr ArmToMidCube();
    frc2::CommandPtr ArmToHighCone();
    frc2::CommandPtr ArmToScoredHighCone();
    frc2::CommandPtr ArmToMidCone();
    frc2::CommandPtr ArmToSafePosition();
    frc2::CommandPtr ArmSafePos();

    frc2::CommandPtr ArmToLoadingStation();
    frc2::CommandPtr ArmToLowCubeOrCone();
    frc2::CommandPtr ArmToDefaultLocation();

    frc2::CommandPtr CubeConeSwitch();
    frc2::CommandPtr ArmToHigh();
    frc2::CommandPtr ArmToMid();

    frc2::CommandPtr ArmPickUp(); 

    frc2::CommandPtr ArmToPos(auto x, auto y);

    frc2::CommandPtr ManualArmMove(double xSpeed, double ySpeed);
    frc2::CommandPtr CoastModeOverride();
    frc2::CommandPtr DriveBottomArmToSwitch();
    frc2::CommandPtr ArmMovesUp();
}