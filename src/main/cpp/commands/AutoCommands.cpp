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
        pathplanner::PathConstraints speed {3_mps,2_mps_sq};
        if (pathName == "PreConeH+C") { speed = {1_mps,1_mps_sq}; }

        auto pathGroup = PathPlanner::loadPathGroup(pathName , {speed});

        int pathNum = 0;
        for (auto path : pathGroup) {
            std::string pathName = fmt::format("auto path {}", pathNum);
            SubDriveBase::GetInstance().DisplayTrajectory(pathName, path.asWPILibTrajectory());
            pathNum++;
        }

        static std::unordered_map<std::string, std::shared_ptr<frc2::Command>> eventMap = {

            {"StartIntake", Intake().Unwrap() },
            // {"StopIntake", ClawClose().AlongWith(StopIntake()).AndThen(StowGamePiece()).Unwrap() },
            {"Stopintake", StopIntake().Unwrap()}, //
            {"StartOuttake", Outtake().Unwrap() },
            {"StopOuttake", StopOuttake().Unwrap() },
            {"ClawClose", ClawClose().Unwrap()}, //
            {"ClawExpand", ClawExpand().Unwrap()}, //

            {"Wait0.5", frc2::cmd::Wait(0.5_s).Unwrap() },
            {"Wait5", frc2::cmd::Wait((5_s)).Unwrap()},

            {"ScoreLowCone", ScorePos(ArmToLowCubeOrCone()).Unwrap() },
            {"ScoreLowCube", ScorePos(ArmToLowCubeOrCone()).Unwrap() },
            {"ScoreMidCone", ScorePos(ArmToMidCone()).Unwrap() },
            {"ScoreMidCube", ScorePos(ArmToMidCube()).Unwrap() },
            {"ScoreHighCone", ScorePos(ArmToHighCone()).Unwrap() }, 
            {"ScoreHighCube", ScorePos(ArmToHighCube()).Unwrap() },

            {"ArmPickUp", ArmPickUp().Unwrap()},
            {"ArmToSafePosition", ArmToSafePosition().Unwrap()},

            {"StowGamePiece", StowGamePiece().Unwrap()},
            {"ArmToDefaultPosition", ArmToDefaultLocation().Unwrap()},

            {"BrakeMode", frc2::cmd::RunOnce([]{ SubDriveBase::GetInstance().SetNeutralMode(NeutralMode::Brake);}).Unwrap()},
    
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
                auto mirroredPose = MirrorPose(pose);
                SubDriveBase::GetInstance().ResetGyroHeading(pose.Rotation().Degrees());
                SubDriveBase::GetInstance().SetPose(mirroredPose);
            },
            {2, 0, 0},
            {1, 0, 0}, // pid value for rotation
            [MirrorPose] (frc::ChassisSpeeds speeds) {
                // auto rotation = frc::Rotation2d.fromRadian(speeds.omega);
                // frc::Pose2d robot_pose_vel = frc::Pose2d(speeds.vx, speeds.vy, rotation);
                // frc::Twist2d twist_vel = frc::Pose2d.log(robot_pose_vel);
                // frc::ChassisSpeeds new_chassis_speed = frc::ChassisSpeeds();

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