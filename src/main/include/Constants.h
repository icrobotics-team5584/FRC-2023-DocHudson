// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */

namespace can {
constexpr int spmLeftMotor = 40;
constexpr int spmRightMotor = 41;

} 
namespace OperatorConstants {

constexpr int kDriverControllerPort = 0;

}  // namespace OperatorConstants

namespace canid {
    // drive base id: 1 - 19
    constexpr int tfxDriveBaseFrontLeftDrive = 1;
    constexpr int tfxDriveBaseFrontLeftTurn = 2;
    constexpr int tfxDriveBaseFrontLeftEncoder = 11;

    constexpr int tfxDriveBaseFrontRightDrive = 7;
    constexpr int tfxDriveBaseFrontRightTurn = 8;
    constexpr int tfxDriveBaseFrontRightEncoder = 10;

    constexpr int tfxDriveBaseBackLeftDrive = 3;
    constexpr int tfxDriveBaseBackLeftTurn = 4;
    constexpr int tfxDriveBaseBackLeftEncoder = 9;

    constexpr int tfxDriveBaseBackRightDrive = 5;
    constexpr int tfxDriveBaseBackRightTurn = 6;
    constexpr int tfxDriveBaseBackRightEncoder = 12;

    // Intake id: 40 - 60

    // Arm id: 20 - 39
}

namespace pcm {
    constexpr int solIntakeOut = 0;
    constexpr int solIntakeIn = 1;
}

namespace dio {
    constexpr int lineBreakPayload = 0;
}
    constexpr int kDriverControllerPort = 0;
}
