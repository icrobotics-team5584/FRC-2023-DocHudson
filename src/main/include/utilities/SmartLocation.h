// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/geometry/Pose2d.h>

class SmartLocation {
 public:
  frc::Pose2d GetAlliancePose();

  SmartLocation(frc::Pose2d pose);

 private:
  frc::Pose2d _pose;
};
