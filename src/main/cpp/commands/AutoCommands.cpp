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

        auto pathGroup = PathPlanner::loadPathGroup(pathName , {{3_mps, 2_mps_sq}, {3_mps, 2_mps_sq}});

        int pathNum = 0;
        for (auto path : pathGroup) {
            std::string pathName = fmt::format("auto path {}", pathNum);
            SubDriveBase::GetInstance().DisplayTrajectory(pathName, path.asWPILibTrajectory());
            pathNum++;
        }

        std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap = {

            {"StartIntake", Intake().Unwrap() },
            {"StopIntake", ClawClose().AlongWith(StopIntake()).AndThen(StowGamePiece()).Unwrap() },
            {"StartOuttake", Outtake().Unwrap() },
            {"StopOuttake", StopOuttake().Unwrap() },
            {"ClawClose", ClawClose().Unwrap()},
            {"ClawExpand", ClawExpand().Unwrap()},

            {"Wait", frc2::cmd::Wait(1_s).Unwrap() },

            {"ScoreLowCone", ScorePos(ArmToLowCubeOrCone()).Unwrap() },
            {"ScoreLowCube", ScorePos(ArmToLowCubeOrCone()).Unwrap() },
            {"ScoreMidCone", ScorePos(ArmToMidCone()).Unwrap() },
            {"ScoreMidCube", ScorePos(ArmToMidCube()).Unwrap() },
            {"ScoreHighCone", ScorePos(ArmToHighCone()).Unwrap() }, 
            {"ScoreHighCube", ScorePos(ArmToHighCube()).Unwrap() },

            {"ArmPickUp", ArmPickUp().Unwrap()},
            {"ArmToSafePosition", ArmToSafePosition().Unwrap()},

            {"StowGamePiece", StowGamePiece().Unwrap()},
    
            {"DoNothing", frc2::cmd::None().Unwrap()}
        };

        auto MirrorPose = [] (frc::Pose2d pose) -> frc::Pose2d {
            if (frc::DriverStation::GetAlliance() == frc::DriverStation::kBlue) {
                return pose;
            }
            units::degree_t rotationDist = 2 * (90_deg - pose.Rotation().Degrees());
            auto mirrorRotation = pose.Rotation().RotateBy(rotationDist);
            return {{16.51_m - pose.X(), pose.Y()}, mirrorRotation};
        };

        static SwerveAutoBuilder autoBuilder{
            [MirrorPose] {
                return MirrorPose(SubDriveBase::GetInstance().GetPose());
            },
            [MirrorPose] (frc::Pose2d pose) {
                SubDriveBase::GetInstance().SetPose(MirrorPose(pose));
                SubDriveBase::GetInstance().ResetGyroHeading(pose.Rotation().Degrees());
            },
            {2, 0, 0},
            {1, 0, 0}, // pid value for rotation
            [MirrorPose] (frc::ChassisSpeeds speeds) {
                if (frc::DriverStation::GetAlliance() == frc::DriverStation::kBlue) {
                    SubDriveBase::GetInstance().Drive(speeds.vx, speeds.vy, speeds.omega, false);
                }
                else {
                    SubDriveBase::GetInstance().Drive(speeds.vx, -speeds.vy, -speeds.omega, false);   
                }
            },
            eventMap,
            {&SubDriveBase::GetInstance()},
            false
        };

        return autoBuilder.fullAuto(pathGroup);
    }

    frc2::CommandPtr ScorePos (frc2::CommandPtr && scoreCommand) {
        using namespace frc2::cmd;

        return ClawClose()
            .AndThen(std::forward<frc2::CommandPtr>(scoreCommand))
            .AndThen(frc2::cmd::Wait(0.5_s))
            .AndThen(ClawExpand());
    }
}