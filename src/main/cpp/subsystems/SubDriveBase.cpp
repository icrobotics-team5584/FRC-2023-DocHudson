// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/MathUtil.h>
#include <frc/RobotBase.h>
#include <units/time.h>

SubDriveBase::SubDriveBase(){
  m_gyro.Calibrate();
  frc::SmartDashboard::PutData("Xcontroller", &Xcontroller);
  frc::SmartDashboard::PutData("field", &_fieldDisplay);
  frc::SmartDashboard::PutData("x controller", &Xcontroller);
  frc::SmartDashboard::PutData("y controller", &Ycontroller);
  frc::SmartDashboard::PutData("rotation controller", &Rcontroller);
  Rcontroller.EnableContinuousInput(-180_deg, 180_deg);
  SyncSensors();
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  frc::SmartDashboard::PutNumber("heading", GetHeading().Degrees().value());
  frc::SmartDashboard::PutNumber("gyro", m_gyro.GetAngle());
  frc::SmartDashboard::PutBoolean("gyro is callibrating", m_gyro.IsCalibrating());
  frc::SmartDashboard::PutNumber("Drivebase speed", GetVelocity().value());

  frc::SmartDashboard::PutNumberArray("drivebase/swervestates", std::array{
    m_frontLeft.GetAngle().Degrees().value(), m_frontLeft.GetSpeed().value(),
    m_frontRight.GetAngle().Degrees().value(), m_frontRight.GetSpeed().value(),
    m_backLeft.GetAngle().Degrees().value(), m_backLeft.GetSpeed().value(),
    m_backRight.GetAngle().Degrees().value(), m_backRight.GetSpeed().value(),
  });
  UpdateOdometry();
}

void SubDriveBase::Drive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rot, bool fieldRelative) {

  // Get states of all swerve modules
  auto states = m_kinematics.ToSwerveModuleStates( fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(
                          xSpeed, ySpeed, rot, GetHeading())
                    : frc::ChassisSpeeds{xSpeed, ySpeed, rot});

  // Set speed limit and apply speed limit to all modules
  m_kinematics.DesaturateWheelSpeeds(&states, MAX_VELOCITY);

  // Setting modules from aquired states
  auto [fl, fr, bl, br] = states;

  frc::SmartDashboard::PutNumberArray("drivebase/requestedstates", std::array{
    fl.angle.Degrees().value(), fl.speed.value(),
    fr.angle.Degrees().value(), fr.speed.value(),
    bl.angle.Degrees().value(), bl.speed.value(),
    br.angle.Degrees().value(), br.speed.value(),
  });

  m_frontLeft.SetDesiredState(fl);
  m_frontRight.SetDesiredState(fr);
  m_backLeft.SetDesiredState(bl);
  m_backRight.SetDesiredState(br);

  // Check if robot is in simulation. 
  // Manualy adjusting gyro by calculating rotation in simulator as gyro is not enabled in simulation
  if (frc::RobotBase::IsSimulation()) {
    units::radian_t radPer20ms = rot * 20_ms;
    units::degree_t newHeading = GetHeading().RotateBy(radPer20ms).Degrees();
    m_gyro.SetAngleAdjustment(-newHeading.value()); // negative to switch to CW from CCW
  }
}

// Syncs encoder values when the robot is turned on
void SubDriveBase::SyncSensors() {
  m_frontLeft.SyncSensors();
  m_frontRight.SyncSensors();
  m_backLeft.SyncSensors();
  m_backRight.SyncSensors();
  m_gyro.Calibrate();
}

frc::Rotation2d SubDriveBase::GetHeading() {
  return m_gyro.GetRotation2d();
}

void SubDriveBase::DriveToTarget(units::meter_t xDistance, units::meter_t yDistance, units::meter_t targetDistance, units::degree_t targetRotation) {
   double speedX = -Xcontroller.Calculate(xDistance.value(), targetDistance.value());
   double speedY = Ycontroller.Calculate(yDistance.value(), 0);
   double speedRot = -Rcontroller.Calculate(targetRotation, 0_deg);
   speedX = std::clamp(speedX, -0.5, 0.5);
   speedY = std::clamp(speedY, -0.5, 0.5);
   speedRot = std::clamp(speedRot, -2.0, 2.0);
   Drive(speedX*1_mps, speedY*1_mps, speedRot*1_rad_per_s, false);
}

// Calculate robot's velocity over past time step (20 ms)
units::meters_per_second_t SubDriveBase::GetVelocity() {
  auto robotDisplacement = _prevPose
    .Translation()
    .Distance(_poseEstimator
      .GetEstimatedPosition()
      .Translation()
    );
  return units::meters_per_second_t{robotDisplacement/20_ms};
}

// calculates the relative field location
void SubDriveBase::UpdateOdometry() {
  auto fl = m_frontLeft.GetPosition();
  auto fr = m_frontRight.GetPosition();
  auto bl = m_backLeft.GetPosition();
  auto br = m_backRight.GetPosition();

  _prevPose = _poseEstimator.GetEstimatedPosition();
  _poseEstimator.Update(GetHeading(), {fl, fr, bl, br});
  _fieldDisplay.SetRobotPose(_poseEstimator.GetEstimatedPosition());
}

void SubDriveBase::DriveToPathPoint(frc::Pose2d& pos, units::meters_per_second_t vel, frc::Rotation2d& rot) {
  auto driveSpeeds = _driveController.Calculate(_poseEstimator.GetEstimatedPosition(), pos, vel, rot);
  Drive(driveSpeeds.vx, driveSpeeds.vy, driveSpeeds.omega, true);
}

void SubDriveBase::ResetGyroHeading() {
  m_gyro.Reset();
}

frc::Pose2d SubDriveBase::GetPose() {return _poseEstimator.GetEstimatedPosition();}

void SubDriveBase::DisplayPose(std::string label, frc::Pose2d pose){
  _fieldDisplay.GetObject(label)->SetPose(pose);
}

void SubDriveBase::UpdatePosition(frc::Pose2d robotPosition) {
  _poseEstimator.AddVisionMeasurement(robotPosition, 2_ms);
}