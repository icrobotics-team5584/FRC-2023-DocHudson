#include "commands/AutoCommands.h"
#include "subsystems/SubDriveBase.h"
#include "commands/GamePieceCommands.h"
#include "commands/ArmCommands.h"
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/SwerveAutoBuilder.h>
#include <unordered_map>
#include <units/time.h>

namespace cmd {

    using namespace pathplanner;

    frc2::CommandPtr PPDrivePath(std::string pathName) {

        std::unordered_map<std::string, std::vector<PathConstraints>> {
        };

        auto pathGroup = PathPlanner::loadPathGroup(pathName , {{5_mps, 3_mps_sq}, {5_mps, 3_mps_sq}});

        int pathNum = 0;
        for (auto path : pathGroup) {
            std::string pathName = fmt::format("auto path {}", pathNum);
            SubDriveBase::GetInstance().DisplayTrajectory(pathName, path.asWPILibTrajectory());
            pathNum++;
        }

        units::time::second_t eventTime = 2_s;

        std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap = {
            {"Intake", Intake().WithTimeout(eventTime).Unwrap() },  
            {"Outtake", Outtake().WithTimeout(eventTime).Unwrap() },

            {"StartIntake", StartIntake().Unwrap() },
            {"StopIntake", StopIntake().Unwrap() },
            {"StartOuttake", StartOuttake().Unwrap() },
            {"StopOuttake", StopOuttake().Unwrap() },

            {"ClawExpand", ClawExpand().WithTimeout(eventTime).Unwrap() },
            {"ClawGrabCone", ClawGrabCone().WithTimeout(eventTime).Unwrap() },
            {"ClawGrabCube", ClawGrabCube().WithTimeout(eventTime).Unwrap() },
            
            {"LeftBumperExtend", LeftBumperExtend().WithTimeout(eventTime).Unwrap() },
            {"RightBumperExtend", RightBumperExtend().WithTimeout(eventTime).Unwrap() },
            {"BothBumperExtend", BothBumperExtend().WithTimeout(eventTime).Unwrap() },

            {"Wait", frc2::cmd::Wait(eventTime).Unwrap() },

            {"ScoreLow", ArmToLowCubeOrCone().AndThen(ClawExpand()).Unwrap() },
            {"ScoreMiddleCone", ArmToMidCone().AndThen(ClawExpand()).Unwrap() },
            {"ScoreMiddleCube", ArmToMidCube().AndThen(ClawExpand()).Unwrap() },
            {"ScoreHighCone", ArmToHighCone().AndThen(ClawExpand()).Unwrap() }, 
            {"ScoreHighCube", ArmToHighCube().AndThen(ClawExpand()).Unwrap() }
        };

        static SwerveAutoBuilder autoBuilder{
            [] { return SubDriveBase::GetInstance().GetPose(); },
            [] (frc::Pose2d pose) { SubDriveBase::GetInstance().SetPose(pose); },
            {0.1, 0, 0},
            {1, 0, 0}, // pid value for rotation
            [] (frc::ChassisSpeeds speeds) {
                SubDriveBase::GetInstance().Drive(speeds.vx, speeds.vy, speeds.omega, false);
            },
            eventMap,
            {&SubDriveBase::GetInstance()}
        };

        return autoBuilder.fullAuto(pathGroup);
    }


}