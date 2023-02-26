
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>
#include <frc/simulation/DCMotorSim.h>

class SubIntake : public frc2::SubsystemBase {
 public:
  SubIntake();

  static SubIntake& GetInstance() {
    static SubIntake inst;
    return inst;
  }

  void Periodic() override;
  void SimulationPeriodic() override;
  void IntakeLeft();
  void IntakeRight();
  void OuttakeLeft();
  void OuttakeRight();
  void Stop();
  void DeployIntake();
  void RetractIntake();
  bool SensesCone();
  
 private:
  ICSparkMax<> _leftMotor{canid::leftMotor};
  ICSparkMax<> _rightMotor{canid::rightMotor};
  ICSparkMax<> _DeployMotor{canid::deployMotor, 2_A};
  frc::DigitalInput _coneSensor{dio::coneSensor};

  double GetIntakeSpeed();

  static constexpr units::turn_t DEPLOY_POS = -13.14289_tr;

  static constexpr double P = 3;
  static constexpr double I = 0.0;
  static constexpr double D = 0.0;
  static constexpr double F = 0.0;

  frc::sim::DCMotorSim _IntakeSim {frc::DCMotor::NEO550(), 1, 0.0001_kg_sq_m};
};
