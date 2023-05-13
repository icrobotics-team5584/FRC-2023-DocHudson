// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"

class SubRollerIntake : public frc2::SubsystemBase {
 public:
  SubRollerIntake();

  static SubRollerIntake& GetInstance() {
    static SubRollerIntake inst;
    return inst;
  }

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void RollerIntake();
  void RollerOuttake();
  void StopRollerIntake();
  void IdleRollerIntake();
  bool GamePieceDetected();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  ICSparkMax<> _rollerMotor{canid::rollerIntakeMotor, 10_A};

};
