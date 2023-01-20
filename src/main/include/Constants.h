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
 
    // Tank Drive Values
  constexpr int TankDriveBaseFrontRight = 3;
  constexpr int TankDriveBaseBackRight = 1;
  constexpr int TankDriveBaseFrontLeft = 5;
  constexpr int TankDriveBaseBackLeft = 6;

    // Intake id: 40 - 60
  constexpr int leftMotor = 40;
  constexpr int rightMotor = 41;
  
    // Arm id: 20 - 39

}
namespace pcm {
  constexpr int ClawGrabLeft = 4; 
  constexpr int ClawGrabRight = 5;
  constexpr int ClawRealeseLeft = 6;
  constexpr int ClawRealeseRight = 7;
  constexpr int leftBumperExtend = 2;
  constexpr int leftBumperRetract = 1;
  constexpr int rightBumperExtend = 0;
  constexpr int rightBumperRetract = 3;
  constexpr int intakeExtend = 8;
  constexpr int intakeRetract = 9;
}
 
namespace dio {
  constexpr int lineBreakPayload = 0;
}
