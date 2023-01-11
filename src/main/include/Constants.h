// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

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

namespace dio {
    constexpr int lineBreakPayload = 0;
}