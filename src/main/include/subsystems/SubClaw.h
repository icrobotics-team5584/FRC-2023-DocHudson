
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"



class SubClaw : public frc2::SubsystemBase {
 public:

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

    SubClaw();
  static SubClaw& GetInstance() {
    static SubClaw inst;
    return inst;
  }



  void Periodic() override;
  void Intake();
  void Stop();
  void Outtake();


 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  ICSparkMax<> _spmIntake{can::spmIntake};
  ICSparkMax<> _spmOuttake{can::spmOuttake};
};
