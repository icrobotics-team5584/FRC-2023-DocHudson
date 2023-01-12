
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>

#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();

  static SubIntake& GetInstance() {
    static SubIntake inst;
    return inst;
  }

  void Periodic() override;
  void IntakeLeft();
  void IntakeRight();
  void OuttakeLeft();
  void OuttakeRight();
  void Stop();
  
 private:
  ICSparkMax<> _leftMotor{canid::leftMotor};
  ICSparkMax<> _rightMotor{canid::rightMotor};
};
