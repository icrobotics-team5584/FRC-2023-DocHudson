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
  // void UpdatePidControllerDrive();
  void DriveToTarget(units::meter_t xDistance, units::meter_t yDistance, units::meter_t targetDistance, units::degree_t targetRotation);

  void Drive(units::meters_per_second_t xSpeed,
             units::meters_per_second_t ySpeed, units::radians_per_second_t rot,
             bool fieldRelative);

  void DriveToPathPoint(frc::Pose2d& pos, units::meters_per_second_t vel, frc::Rotation2d& rot);

  frc::Pose2d GetPose();
  void DisplayPose(std::string label, frc::Pose2d pose);
             
  void UpdateOdometry();
  void SyncSensors();
  frc::Rotation2d GetHeading();
  units::meters_per_second_t GetVelocity();

  static constexpr units::meters_per_second_t MAX_VELOCITY = 3_mps;
  static constexpr units::radians_per_second_t MAX_ANGULAR_VELOCITY =
      180_deg_per_s;

  static constexpr units::radians_per_second_squared_t MAX_ANGULAR_ACCEL{
      std::numbers::pi};

  void ResetGyroHeading();
  void UpdatePosition(frc::Pose2d robotPosition);

 private:
  SubDriveBase();
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  AHRS m_gyro{frc::SerialPort::kMXP};

  frc::Translation2d m_frontLeftLocation{+0.281_m, +0.281_m};
  frc::Translation2d m_frontRightLocation{+0.281_m, -0.281_m};
  frc::Translation2d m_backLeftLocation{-0.281_m, +0.281_m};
  frc::Translation2d m_backRightLocation{-0.281_m, -0.281_m};

  const double FRONT_LEFT_MAG_OFFSET = 16.00;//-13.97;//-166.9;
  const double FRONT_RIGHT_MAG_OFFSET = -136.14;//-111.30;//108.5;
  const double BACK_LEFT_MAG_OFFSET = 108.63;//-149.68;//148.7;
  const double BACK_RIGHT_MAG_OFFSET = -31.64;//-44.82;//-136.05;

  SwerveModule m_frontLeft{canid::DriveBaseFrontLeftDrive, canid::DriveBaseFrontLeftTurn, canid::DriveBaseFrontLeftEncoder, FRONT_LEFT_MAG_OFFSET};
  SwerveModule m_frontRight{canid::DriveBaseFrontRightDrive, canid::DriveBaseFrontRightTurn, canid::DriveBaseFrontRightEncoder, FRONT_RIGHT_MAG_OFFSET};
  SwerveModule m_backLeft{canid::DriveBaseBackLeftDrive, canid::DriveBaseBackLeftTurn, canid::DriveBaseBackLeftEncoder, BACK_LEFT_MAG_OFFSET};
  SwerveModule m_backRight{canid::DriveBaseBackRightDrive, canid::DriveBaseBackRightTurn, canid::DriveBaseBackRightEncoder, BACK_RIGHT_MAG_OFFSET};

  frc::SwerveDriveKinematics<4> m_kinematics{
      m_frontLeftLocation, m_frontRightLocation, m_backLeftLocation,
      m_backRightLocation};

	
  frc::SwerveDriveOdometry<4> m_odometry{m_kinematics, m_gyro.GetRotation2d(), {frc::SwerveModulePosition{0_m, m_frontLeft.GetAngle()}, 
				frc::SwerveModulePosition{0_m, m_frontRight.GetAngle()}, frc::SwerveModulePosition{0_m, m_backLeft.GetAngle()}, frc::SwerveModulePosition{0_m, m_backRight.GetAngle()}}};

  frc::PIDController Xcontroller{0.1,0,0};
  frc::PIDController Ycontroller{0.1,0,0};
  frc::ProfiledPIDController<units::radian> Rcontroller{1.8,0,0,{MAX_ANGULAR_VELOCITY, MAX_ANGULAR_ACCEL}};
  frc::HolonomicDriveController _driveController{Xcontroller, Ycontroller, Rcontroller};

  // const wpi::array<frc::SwerveModulePosition, 4> modulePositions = {frc::SwerveModulePosition{0_m, m_frontLeft.GetAngle()}, 
	// 			frc::SwerveModulePosition{0_m, m_frontRight.GetAngle()}, frc::SwerveModulePosition{0_m, m_backLeft.GetAngle()}, frc::SwerveModulePosition{0_m, m_backRight.GetAngle()}};

  frc::SwerveDrivePoseEstimator<4> _poseEstimator{
      m_kinematics, m_gyro.GetRotation2d(), {frc::SwerveModulePosition{0_m, m_frontLeft.GetAngle()}, 
				frc::SwerveModulePosition{0_m, m_frontRight.GetAngle()}, frc::SwerveModulePosition{0_m, m_backLeft.GetAngle()}, frc::SwerveModulePosition{0_m, m_backRight.GetAngle()}} ,frc::Pose2d()
  };
  frc::Pose2d _prevPose; // Used for velocity calculations

  frc::Field2d _fieldDisplay;
};
 