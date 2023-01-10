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

namespace canid {
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

  //For tank drive
  constexpr int spmDriveBaseFrontRight = 3;
  constexpr int spmDriveBaseBackRight = 1;
  constexpr int spmDriveBaseFrontLeft = 4;
  constexpr int spmDriveBaseBackLeft = 2;

  constexpr int tfxIntake = 14;
  constexpr int spmPayload = 99;
  constexpr int spmPayloadFollow = 98;
}

namespace OperatorConstants {

constexpr int kDriverControllerPort = 0;

}  // namespace OperatorConstants
