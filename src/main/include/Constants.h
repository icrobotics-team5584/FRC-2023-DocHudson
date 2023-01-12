// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

<<<<<<< HEAD
/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace OperatorConstants {

constexpr int kDriverControllerPort = 0;

}  // namespace OperatorConstants
=======
namespace canid {
    // drive base id: 1 - 19
    constexpr int DriveBaseFrontLeftDrive = 1;
    constexpr int DriveBaseFrontLeftTurn = 2;
    constexpr int DriveBaseFrontLeftEncoder = 11;

    constexpr int DriveBaseFrontRightDrive = 7;
    constexpr int DriveBaseFrontRightTurn = 8;
    constexpr int DriveBaseFrontRightEncoder = 10;

    constexpr int DriveBaseBackLeftDrive = 3;
    constexpr int DriveBaseBackLeftTurn = 4;
    constexpr int DriveBaseBackLeftEncoder = 9;

    constexpr int DriveBaseBackRightDrive = 5;
    constexpr int DriveBaseBackRightTurn = 6;
    constexpr int DriveBaseBackRightEncoder = 12;

    // Intake id: 40 - 60
    constexpr int leftMotor = 40;
    constexpr int rightMotor = 41;
    // Arm id: 20 - 39

}
namespace pcm {
    constexpr int ClawGrabLeft = 0; 
    constexpr int ClawGrabRight = 1;
    constexpr int ClawRealeseLeft = 2;
    constexpr int ClawRealeseRight = 3;
}

namespace dio {
    constexpr int lineBreakPayload = 0;
}
>>>>>>> master
