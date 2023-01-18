#include "commands/DriveCommands.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubVision.h"

namespace cmd {
    using namespace frc2::cmd;

    frc2::CommandPtr AddVisionMeasurement() {
        return Run([] {
            auto result = SubVision::GetInstance().GetMeasurement();
           if (result.has_value()) {
           
            auto [pose, latency, ambiguity] = result.value();
            SubDriveBase::GetInstance().AddVisionMeasurement(pose.ToPose2d(), ambiguity, latency);
           }
        }, {&SubVision::GetInstance()});
      
    }
}