// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

namespace canivore {
  constexpr int DriveBaseFrontLeftDrive = 7;
  constexpr int DriveBaseFrontLeftTurn = 8;
  constexpr int DriveBaseFrontLeftEncoder = 10;

  constexpr int DriveBaseFrontRightDrive = 5;
  constexpr int DriveBaseFrontRightTurn = 6;
  constexpr int DriveBaseFrontRightEncoder = 12;

  constexpr int DriveBaseBackLeftDrive = 1;
  constexpr int DriveBaseBackLeftTurn = 2;
  constexpr int DriveBaseBackLeftEncoder = 11;

  constexpr int DriveBaseBackRightDrive = 3;
  constexpr int DriveBaseBackRightTurn = 4;
  constexpr int DriveBaseBackRightEncoder = 9;
}

namespace canid {
  // Intake id: 01 - 09
  constexpr int leftMotor = 1;
  constexpr int rightMotor = 2;
  constexpr int deployMotor = 3;
  
  // Arm id: 10 - 19
  constexpr int armMotorBottom = 10;
  constexpr int armMotorBottomFollow = 11;
  constexpr int armMotorTop = 13;
  constexpr int armMotorTopFollow = 12;

  //Claw id: 20-29
  constexpr int clawMotor1 = 20;
}
 
namespace dio {
    constexpr int armBottomSensor = 9;
    constexpr int breakModeSwitch = 6;
    constexpr int armTopSensor = 1;
    constexpr int coneSensor = 2;
    constexpr int clawSensor = 8;
}

namespace pwm {
  constexpr int LEDs = 0;
}
