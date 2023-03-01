#include "commands/DriveCommands.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubVision.h"
#include "utilities/Grids.h"
#include "RobotContainer.h"
#include "subsystems/SubLED.h"
#include <frc/DriverStation.h>

namespace cmd {
using namespace frc2::cmd;

frc2::CommandPtr AddVisionMeasurement() {
  return Run(
      [] {
        auto estimatedPose = SubVision::GetInstance().GetMeasurement();
        frc::SmartDashboard::PutBoolean("Vision/is teleop", frc::DriverStation::IsTeleop());
        frc::SmartDashboard::PutBoolean("Vision/has value", estimatedPose.has_value());
        if (estimatedPose.has_value() && frc::DriverStation::IsTeleop()) {
          auto estimatedPoseValue = estimatedPose.value();
          SubDriveBase::GetInstance().AddVisionMeasurement(
              estimatedPoseValue.estimatedPose.ToPose2d(), 0,
              estimatedPoseValue.timestamp);
          SubDriveBase::GetInstance().DisplayPose(
              "EstimatedPose", estimatedPoseValue.estimatedPose.ToPose2d());
        } else {
          SubDriveBase::GetInstance().DisplayPose("EstimatedPose", {});
        }
      },
      {&SubVision::GetInstance()});
}

frc2::CommandPtr DriveToPose(std::function<frc::Pose2d()> targetPoseGetter) {
  return Run(
             [=] {
               SubLED::autoDriving = true;
               SubDriveBase::GetInstance().DriveToPose(targetPoseGetter());
             },
             {&SubDriveBase::GetInstance()})
      .Until([=] {
        return SubDriveBase::GetInstance().IsAtPose(targetPoseGetter());
      })
      .FinallyDo([](bool _) { SubLED::autoDriving = false; });
}

}  // namespace cmd
