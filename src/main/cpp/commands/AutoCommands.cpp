#include "commands/AutoCommands.h"
#include "subsystems/SubDriveBase.h"
#include "commands/GamePieceCommands.h"
#include "commands/ArmCommands.h"
#include "commands/DriveCommands.h"
#include <pathplanner/lib/PathPlanner.h>
#include <pathplanner/lib/auto/SwerveAutoBuilder.h>
#include <unordered_map>
#include <units/time.h>
#include <constants.h>

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

            {"StartRollerIntake", StartRollerIntake().Unwrap() },
            {"StopRollerIntake",  StopRollerIntake().Unwrap() },
            {"StartRollerOuttake", StartRollerOuttake().Unwrap() },
            {"StopRollerOuttake", StopRollerOuttake().Unwrap() },

            {"RollerIntake1s", RollerIntake().WithTimeout(1_s).Unwrap() },
            {"RollerOuttake1s", RollerOuttake().WithTimeout(1_s).Unwrap() },

            {"Wait0.5", frc2::cmd::Wait(0.5_s).Unwrap() },
            {"Wait1.5", frc2::cmd::Wait(1.5_s).Unwrap()},
            {"Wait5", frc2::cmd::Wait((5_s)).Unwrap()},

            {"ScoreLowCone", ScorePos(ArmToLowCubeOrCone()).Unwrap() },
            {"ScoreLowCube", ScorePos(ArmToLowCubeOrCone()).Unwrap() },
            {"ScoreMidCone", ScorePos(ArmToMidCone()).Unwrap() },
            {"ScoreMidCube", ScorePos(ArmToMidCube()).Unwrap() },
            {"ScoreHighCone", ScorePos(ArmToHighCone().AndThen(ArmToScoredHighCone())).Unwrap() }, 
            {"ScoreHighCube", ScorePos(ArmToHighCube()).Unwrap() },

            {"ArmPickUp", ArmPickUp().Unwrap()},
            {"ArmToSafePosition", ArmToSafePosition().Unwrap()},
            {"ArmSafePos", ArmSafePos().Unwrap()},

            {"ArmToDefaultPosition", ArmToDefaultLocation().Unwrap()},

            {"BrakeMode", frc2::cmd::RunOnce([]{ SubDriveBase::GetInstance().SetNeutralMode(NeutralMode::Brake);}).Unwrap()},

            {"AutoBalance", cmd::AutoBalance().Unwrap()},
    
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
                units::radian_t rotation = speeds.omega * 20_ms;
                frc::Pose2d robot_pose_vel = frc::Pose2d(speeds.vx * 20_ms, speeds.vy * 20_ms, frc::Rotation2d(rotation));
                frc::Twist2d twist_vel = frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)).Log(robot_pose_vel);

                units::velocity::meters_per_second_t new_x = twist_vel.dx / 20_ms;
                units::velocity::meters_per_second_t new_y = twist_vel.dy / 20_ms;
                units::radians_per_second_t new_r = twist_vel.dtheta / 20_ms;

                // units::velocity::meters_per_second_t new_x = speeds.vx;
                // units::velocity::meters_per_second_t new_y = speeds.vy * 0.4;
                // units::radians_per_second_t new_r = speeds.omega;



                if (frc::DriverStation::GetAlliance() == frc::DriverStation::kBlue) {
                    SubDriveBase::GetInstance().Drive(speeds.vx, speeds.vy, speeds.omega, false);
                    // SubDriveBase::GetInstance().Drive(speeds.vx, speeds.vy, speeds.omega, false);
                }
                else {
                    SubDriveBase::GetInstance().Drive(new_x, -new_y, -new_r, false);
                    // SubDriveBase::GetInstance().Drive(speeds.vx, -speeds.vy, -speeds.omega, false);
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

        return std::forward<frc2::CommandPtr>(scoreCommand);
    }   
}