#pragma once

#include <frc/geometry/Pose2d.h>
#include <frc2/command/Commands.h>
#include <frc/XboxController.h>

namespace cmd {
  frc2::CommandPtr  AddVisionMeasurement();

  //Grid drive commands
  frc2::CommandPtr DriveToPose(std::function<frc::Pose2d()> targetPoseGetter);

  //auto balancing
  frc2::CommandPtr AutoBalance();
  frc2::CommandPtr DriveBackwards();

  //driving to angle
  frc2::CommandPtr SnapToAngle();
  frc2::CommandPtr Drive(frc::XboxController &controller);
  
}
