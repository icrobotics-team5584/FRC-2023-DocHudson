#include "commands/DriveCommands.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubVision.h"
#include "utilities/Grids.h"
#include "RobotContainer.h"
#include "subsystems/SubLED.h"

namespace cmd {
using namespace frc2::cmd;

frc2::CommandPtr AddVisionMeasurement() {
  return Run(
      [] {
        auto result = SubVision::GetInstance().GetMeasurement();
        if (result.has_value()) {
          auto [pose, timeStamp, ambiguity] = result.value();
          SubDriveBase::GetInstance().AddVisionMeasurement(
              pose.ToPose2d(), ambiguity, timeStamp);
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
