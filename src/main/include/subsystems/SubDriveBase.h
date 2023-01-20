// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once


#include <frc2/command/SubsystemBase.h>

#include <AHRS.h>
#include <frc/geometry/Translation2d.h>
#include <frc/kinematics/SwerveDriveKinematics.h>
#include <frc/kinematics/SwerveDriveOdometry.h>
#include <frc/estimator/SwerveDrivePoseEstimator.h>
#include <frc/smartdashboard/Field2d.h>
#include <frc/controller/HolonomicDriveController.h>

#include <numbers>

#include "Constants.h"
#include "utilities/SwerveModule.h"

class SubDriveBase : public frc2::SubsystemBase {
 public:
  void Periodic() override;

  static SubDriveBase& GetInstance() {
    static SubDriveBase inst;
    return inst;
  }
  void AddVisionMeasurement(frc::Pose2d pose, double ambiguity, units::second_t latency);
  // void UpdatePidControllerDrive();
  void DriveToTarget(units::meter_t xDistance, units::meter_t yDistance, 
                  units::meter_t targetDistance, units::degree_t targetRotation);

  void Drive(units::meters_per_second_t xSpeed,
             units::meters_per_second_t ySpeed, units::degrees_per_second_t rot,
             bool fieldRelative);

  void DriveToPathPoint(frc::Pose2d& pos, units::meters_per_second_t vel, frc::Rotation2d& rot);

  frc::Pose2d GetPose();
  void SetPose(frc::Pose2d pose);
  void DisplayPose(std::string label, frc::Pose2d pose);
             
  void UpdateOdometry();
  void SyncSensors();
  frc::Rotation2d GetHeading();
  units::meters_per_second_t GetVelocity();
  frc::SwerveDriveKinematics<4> GetKinematics();

  static constexpr units::meters_per_second_t MAX_VELOCITY = 3_mps;
  static constexpr units::degrees_per_second_t MAX_ANGULAR_VELOCITY =
      180_deg_per_s;

  static constexpr units::radians_per_second_squared_t MAX_ANGULAR_ACCEL{
      std::numbers::pi};

  void ResetGyroHeading();
  void UpdatePosition(frc::Pose2d robotPosition);
    frc::Field2d _fieldDisplay;
 


  void DisplayTrajectory(std::string name, frc::Trajectory trajectory);

 private:
  SubDriveBase();
  AHRS _gyro{frc::SerialPort::kMXP};

  frc::Translation2d _frontLeftLocation{+0.281_m, +0.281_m};
  frc::Translation2d _frontRightLocation{+0.281_m, -0.281_m};
  frc::Translation2d _backLeftLocation{-0.281_m, +0.281_m};
  frc::Translation2d _backRightLocation{-0.281_m, -0.281_m};

  const double FRONT_LEFT_MAG_OFFSET = 16.00;//-13.97;//-166.9;
  const double FRONT_RIGHT_MAG_OFFSET = -136.14;//-111.30;//108.5;
  const double BACK_LEFT_MAG_OFFSET = 108.63;//-149.68;//148.7;
  const double BACK_RIGHT_MAG_OFFSET = -31.64;//-44.82;//-136.05;

  SwerveModule _frontLeft{canid::DriveBaseFrontLeftDrive, canid::DriveBaseFrontLeftTurn, canid::DriveBaseFrontLeftEncoder, FRONT_LEFT_MAG_OFFSET};
  SwerveModule _frontRight{canid::DriveBaseFrontRightDrive, canid::DriveBaseFrontRightTurn, canid::DriveBaseFrontRightEncoder, FRONT_RIGHT_MAG_OFFSET};
  SwerveModule _backLeft{canid::DriveBaseBackLeftDrive, canid::DriveBaseBackLeftTurn, canid::DriveBaseBackLeftEncoder, BACK_LEFT_MAG_OFFSET};
  SwerveModule _backRight{canid::DriveBaseBackRightDrive, canid::DriveBaseBackRightTurn, canid::DriveBaseBackRightEncoder, BACK_RIGHT_MAG_OFFSET};

  frc::SwerveDriveKinematics<4> _kinematics{
      _frontLeftLocation, _frontRightLocation, _backLeftLocation,
      _backRightLocation};

  frc::PIDController Xcontroller{0.1,0,0};
  frc::PIDController Ycontroller{0.1,0,0};
  frc::ProfiledPIDController<units::radian> Rcontroller{1.8,0,0,{MAX_ANGULAR_VELOCITY, MAX_ANGULAR_ACCEL}};
  frc::HolonomicDriveController _driveController{Xcontroller, Ycontroller, Rcontroller};

  frc::SwerveDrivePoseEstimator<4> _poseEstimator{
      _kinematics, _gyro.GetRotation2d(), {frc::SwerveModulePosition{0_m, _frontLeft.GetAngle()}, 
				  frc::SwerveModulePosition{0_m, _frontRight.GetAngle()}, frc::SwerveModulePosition{0_m, _backLeft.GetAngle()}, 
          frc::SwerveModulePosition{0_m, _backRight.GetAngle()}} ,frc::Pose2d(),
          {0.3, 0.6, 0.3},
          {0.7, 0.4, 0.7}
  };

  frc::Pose2d _prevPose; // Used for velocity calculations
};;
 