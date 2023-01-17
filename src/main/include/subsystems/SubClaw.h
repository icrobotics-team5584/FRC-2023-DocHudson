// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DoubleSolenoid.h>
#include "Constants.h"
#include <frc/smartdashboard/SmartDashboard.h>

class SubClaw : public frc2::SubsystemBase {
 public:
  SubClaw();
static SubClaw &GetInstance() {static SubClaw inst; return inst;}
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void BothExtended();
  void OneExtended();
  void OneRetracted();
  void BothRetracted();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::DoubleSolenoid _solPnuematicsLeft{0, frc::PneumaticsModuleType::CTREPCM,pcm::ClawGrabLeft,pcm::ClawRealeseLeft};
  frc::DoubleSolenoid _solPnuematicsRight{0, frc::PneumaticsModuleType::CTREPCM,pcm::ClawGrabRight,pcm::ClawRealeseRight};
};
