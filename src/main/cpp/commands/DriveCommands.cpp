#include "commands/DriveCommands.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubVision.h"
#include "RobotContainer.h"
#include "subsystems/SubLED.h"
#include "subsystems/SubArm.h"
#include <frc/DriverStation.h>
#include <frc/filter/SlewRateLimiter.h>
#include <frc/MathUtil.h>
#include <units/angle.h>

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

  frc2::CommandPtr AutoBalance(){

    return Run([]{
      units::meters_per_second_t speed = 0.1_mps;
      units::radians_per_second_t rotSpeed = 0_rad_per_s;
      units::degree_t robotPitchAngle = SubDriveBase::GetInstance().GetPitch();
      frc::SmartDashboard::PutNumber("Pitch Angle", robotPitchAngle.value());
      if(robotPitchAngle > 7_deg) {
        SubDriveBase::GetInstance().Drive(speed, 0_mps, rotSpeed, false); // 
      }
      else if (robotPitchAngle < -7_deg) {
        SubDriveBase::GetInstance().Drive(-speed, 0_mps, rotSpeed, false);
      }
      else{
        SubDriveBase::GetInstance().Drive(0_mps, 0_mps, rotSpeed, false);
      }
      });

  };

  frc2::CommandPtr DriveBackwards() {
    return Run([]{
      SubDriveBase::GetInstance().Drive(-0.1_mps, 0_mps, 0_rad_per_s, false);
    });
  }

  frc2::CommandPtr Drive(frc::XboxController &controller){
    return Run([&controller]{
      
      frc::SlewRateLimiter<units::scalar> xspeedLimiter{3 / 1_s};
      frc::SlewRateLimiter<units::scalar> yspeedLimiter{3 / 1_s};
      frc::SlewRateLimiter<units::scalar> rotLimiter{3 / 1_s};

      const double deadband = 0.08;
      const auto xSpeed = -xspeedLimiter.Calculate(frc::ApplyDeadband(controller.GetLeftY(), deadband)) * SubDriveBase::MAX_VELOCITY;
      const auto ySpeed = -yspeedLimiter.Calculate(frc::ApplyDeadband(controller.GetLeftX(), deadband)) * SubDriveBase::MAX_VELOCITY;
      const auto rot = -rotLimiter.Calculate(frc::ApplyDeadband(controller.GetRightX(), deadband)) * SubDriveBase::MAX_ANGULAR_VELOCITY;
      //SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, true);
      
      if (SubArm::GetInstance().GetEndEffectorTarget().Y() > 90_cm){SubDriveBase::GetInstance().Drive(xSpeed/2, ySpeed/2, rot/2, false);}
      else if (controller.GetLeftStickButton()){SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, false);}
      else {SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, true);} //true == field relative
    });
  }

  frc2::CommandPtr SnapToAngleWhileDriving(frc::XboxController &controller, units::radian_t targetAngle){
    return Run([&controller]{
      
      frc::SlewRateLimiter<units::scalar> xspeedLimiter{3 / 1_s};
      frc::SlewRateLimiter<units::scalar> yspeedLimiter{3 / 1_s};
      frc::SlewRateLimiter<units::scalar> rotLimiter{3 / 1_s};

      const double deadband = 0.08;
      const auto xSpeed = -xspeedLimiter.Calculate(frc::ApplyDeadband(controller.GetLeftY(), deadband)) * SubDriveBase::MAX_VELOCITY;
      const auto ySpeed = -yspeedLimiter.Calculate(frc::ApplyDeadband(controller.GetLeftX(), deadband)) * SubDriveBase::MAX_VELOCITY;

      
      //SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, true);
      
      if (SubArm::GetInstance().GetEndEffectorTarget().Y() > 90_cm){SubDriveBase::GetInstance().Drive(xSpeed/2, ySpeed/2, rot/2, false);}
      else if (controller.GetLeftStickButton()){SubDriveBase::GetInstance().Drive(xSpeed, ySpeed, rot, false);}
      else {SubDriveBase::GetInstance().SnapToAngleWhileDriving(xSpeed, ySpeed, targetAngle, true);} //true == field relative
    });
  }

  /*
  }
  void SubDriveBase::RotateTowardZero(units::degree_t angle) {
    double turnRate = _rotController.Calculate(0, angle.value());
    Drive(0, turnRate);
  }

  */
} // namespace cmd
