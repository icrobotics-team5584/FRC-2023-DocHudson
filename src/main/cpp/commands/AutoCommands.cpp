#include "commands/AutoCommands.h"
#include "subsystems/SubDriveBase.h"
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/SwerveAutoBuilder.h>
#include <unordered_map>

namespace cmd {

    using namespace pathplanner;

    frc2::CommandPtr PPDrivePath() { // name of pathplanner required in line 12
        auto pathGroup = PathPlanner::loadPathGroup("Hudson#1", {{5_mps, 3_mps_sq}, {5_mps, 3_mps_sq}});

        int pathNum = 0;
        for (auto path : pathGroup) {
            std::string pathName = fmt::format("auto path {}", pathNum);
            SubDriveBase::GetInstance().DisplayTrajectory(pathName, path.asWPILibTrajectory());
            pathNum++;
        }

        std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap {
            // {"Intake", },
            // {"Drive", },
            // {"Score", },
        };

        static SwerveAutoBuilder autoBuilder{
            [] { return SubDriveBase::GetInstance().GetPose(); },
            [] (frc::Pose2d pose) { SubDriveBase::GetInstance().SetPose(pose); },
            SubDriveBase::GetInstance().GetKinematics(),
            {0.1, 0, 0},
            {0.1, 0, 0},
            [] (frc::ChassisSpeeds speeds) {
                SubDriveBase::GetInstance().Drive(speeds.vx, speeds.vy, speeds.omega, true);
            },
            eventMap,
            {&SubDriveBase::GetInstance()}
        };

        return autoBuilder.fullAuto(pathGroup);
    }


}