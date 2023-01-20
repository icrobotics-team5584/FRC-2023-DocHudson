// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc/XboxController.h>
#include <units/dimensionless.h>

class CmdDriveRobot
    : public frc2::CommandHelper<frc2::CommandBase, CmdDriveRobot> {
 public:
  CmdDriveRobot(frc::XboxController* controller);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;
  frc::SlewRateLimiter<units::scalar> _xspeedLimiter{3 / 1_s};
  frc::SlewRateLimiter<units::scalar> _yspeedLimiter{3 / 1_s};
  frc::SlewRateLimiter<units::scalar> _rotLimiter{3 / 1_s};
  frc::XboxController* _controller;

};
