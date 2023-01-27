
// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "utilities/ICSparkMax.h"
#include "Constants.h"
#include <frc/DigitalInput.h>
#include <frc/DoubleSolenoid.h>

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
  
  void StopBumper();
  void BothBumperExtended();
  void LeftBumperExtended();
  void LeftBumperRetracted();
  void RightBumperRetracted();
  void RightBumperExtended();
  void OneBumperRetracted();
  void BothBumperRetracted();
  bool SensesCone();
  
 private:
  ICSparkMax<> _leftMotor{canid::leftMotor};
  ICSparkMax<> _rightMotor{canid::rightMotor};
  frc::DigitalInput _coneSensor{dio::coneSensor};
  frc::DoubleSolenoid _solPneumaicsLeftBumper{0, frc::PneumaticsModuleType::CTREPCM,pcm::leftBumperExtend,pcm::rightBumperRetract};
  frc::DoubleSolenoid _solPneumaticsRightBumper{0, frc::PneumaticsModuleType::CTREPCM,pcm::rightBumperExtend,pcm::leftBumperRetract};
};
