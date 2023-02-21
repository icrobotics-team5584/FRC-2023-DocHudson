// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "utilities/ICSparkMax.h"
#include <units/angle.h>
#include <rev/SparkMaxAbsoluteEncoder.h>
#include <frc/simulation/DCMotorSim.h>

class SubClaw : public frc2::SubsystemBase {
 public:
  SubClaw();

  static SubClaw& GetInstance() {
    static SubClaw inst;
    return inst;
  }
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void ClawClampedCube();
  void ClawClampedCone();
  void ClawUnclamped();

  void SimulationPeriodic() override;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  ICSparkMax<> _clawMotor1{canid::clawMotor1};

  rev::SparkMaxAbsoluteEncoder _clawEncoder{_clawMotor1.GetAbsoluteEncoder(rev::SparkMaxAbsoluteEncoder::Type::kDutyCycle)};

  static constexpr double P = 4.5;
  static constexpr double I = 0.0;
  static constexpr double D = 0.0;
  static constexpr double F = 0.0;

  // simulation stuff
  frc::sim::DCMotorSim _clawSim{frc::DCMotor::NEO550(), 1, 0.0001_kg_sq_m};
};
