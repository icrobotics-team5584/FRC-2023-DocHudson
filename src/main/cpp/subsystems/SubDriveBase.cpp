// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubDriveBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/MathUtil.h>
#include <frc/RobotBase.h>
#include <units/time.h> 
#include <frc/DriverStation.h>

SubDriveBase::SubDriveBase(){
  _gyro.Calibrate();
  Rcontroller.EnableContinuousInput(-180_deg, 180_deg);
  SyncSensors();

  // Dashboard Displays:
  // frc::SmartDashboard::PutData("Xcontroller", &Xcontroller);
   frc::SmartDashboard::PutData("field", &_fieldDisplay);
  // frc::SmartDashboard::PutData("x controller", &Xcontroller);
  // frc::SmartDashboard::PutData("y controller", &Ycontroller);
  // frc::SmartDashboard::PutData("rotation controller", &Rcontroller);
}

// This method will be called once per scheduler run
void SubDriveBase::Periodic() {
  auto loopStart = frc::GetTime();
  // Dashboard Displays:
  frc::SmartDashboard::PutNumber("drivebase/heading", GetHeading().Degrees().value());
  frc::SmartDashboard::PutNumber("Drivebase/velocity", GetVelocity().value());

  frc::SmartDashboard::PutNumberArray("drivebase/true swerve states", std::array{
    _frontLeft.GetAngle().Degrees().value(), _frontLeft.GetSpeed().value(),
    _frontRight.GetAngle().Degrees().value(), _frontRight.GetSpeed().value(),
    _backLeft.GetAngle().Degrees().value(), _backLeft.GetSpeed().value(),
     _backRight.GetAngle().Degrees().value(), _backRight.GetSpeed().value(),
   });

   UpdateOdometry();
  frc::SmartDashboard::PutNumber("drivebase/loop time (sec)", (frc::GetTime()-loopStart).value());
}

void SubDriveBase::Drive(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, 
                      units::degrees_per_second_t rot, bool fieldRelative) {

  // Get states of all swerve modules
  auto states = _kinematics.ToSwerveModuleStates( fieldRelative ? frc::ChassisSpeeds::FromFieldRelativeSpeeds(
                          xSpeed, ySpeed, rot, GetHeading()) : frc::ChassisSpeeds{xSpeed, ySpeed, rot});

  // Set speed limit and apply speed limit to all modules
  _kinematics.DesaturateWheelSpeeds(&states, MAX_VELOCITY);

  // Setting modules from aquired states
  auto [fl, fr, bl, br] = states;

  // Dashboard Displays:
  frc::SmartDashboard::PutNumberArray("drivebase/desired swerve states", std::array{
    fl.angle.Degrees().value(), fl.speed.value(),
    fr.angle.Degrees().value(), fr.speed.value(),
    bl.angle.Degrees().value(), bl.speed.value(),
    br.angle.Degrees().value(), br.speed.value(),
  });

  _frontLeft.SetDesiredState(fl);
  _frontRight.SetDesiredState(fr);
  _backLeft.SetDesiredState(bl);
  _backRight.SetDesiredState(br);

  // Check if robot is in simulation. 
  // Manualy adjusting gyro by calculating rotation in simulator as gyro is not enabled in simulation
  if (frc::RobotBase::IsSimulation()) {
    units::radian_t radPer20ms = rot * 20_ms;
    units::degree_t newHeading = GetHeading().RotateBy(radPer20ms).Degrees();
    _gyro.SetAngleAdjustment(-newHeading.value()); // negative to switch to CW from CCW
  }

  _frontLeft.SendSensorsToDash();
  _frontRight.SendSensorsToDash();
  _backLeft.SendSensorsToDash();
  _backRight.SendSensorsToDash();
}

// Syncs encoder values when the robot is turned on
void SubDriveBase::SyncSensors() {
  _frontLeft.SyncSensors();
  _frontRight.SyncSensors();
  _backLeft.SyncSensors();
  _backRight.SyncSensors();
  _gyro.Calibrate();
}

frc::Rotation2d SubDriveBase::GetHeading() {
  return _gyro.GetRotation2d();
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

frc::SwerveDriveKinematics<4> SubDriveBase::GetKinematics() {
  return _kinematics;
}

// calculates the relative field location
void SubDriveBase::UpdateOdometry() {
  auto fl = _frontLeft.GetPosition();
  auto fr = _frontRight.GetPosition();
  auto bl = _backLeft.GetPosition();
  auto br = _backRight.GetPosition();

  _prevPose = _poseEstimator.GetEstimatedPosition();
  _poseEstimator.Update(GetHeading(), {fl, fr, bl, br});
  _fieldDisplay.SetRobotPose(_poseEstimator.GetEstimatedPosition());  
}

void SubDriveBase::DriveToPose(frc::Pose2d targetPose) {
  DisplayPose("targetPose", targetPose);

  frc::Pose2d currentPosition = _poseEstimator.GetEstimatedPosition();
  double speedX = Xcontroller.Calculate(currentPosition.X().value(), targetPose.X().value());
  double speedY = Ycontroller.Calculate(currentPosition.Y().value(), targetPose.Y().value());
  double speedRot = Rcontroller.Calculate(currentPosition.Rotation().Radians(), targetPose.Rotation().Radians()); 
  
  speedX = std::clamp(speedX, -0.5, 0.5);
  speedY = std::clamp(speedY, -0.5, 0.5);
  speedRot = std::clamp(speedRot, -2.0, 2.0);

  // Drive speeds are relative to your alliance wall. Flip if we are on red, 
  // since we are using global coordinates (blue alliance at 0,0)
  if (frc::DriverStation::GetAlliance() == frc::DriverStation::kRed && frc::RobotBase::IsReal()) {
    Drive(-speedX*1_mps, -speedY*1_mps, speedRot*1_rad_per_s, true);
  } else {
    Drive(speedX*1_mps, speedY*1_mps, speedRot*1_rad_per_s, true);
  }
}

bool SubDriveBase::IsAtPose(frc::Pose2d pose) {
  auto currentPose = _poseEstimator.GetEstimatedPosition();
  auto rotError = currentPose.Rotation() - pose.Rotation();
  auto posError = currentPose.Translation().Distance(pose.Translation());
  
  if (units::math::abs(rotError.Degrees()) < 1_deg && posError < 1_cm) {
     return true;
  } else {return false;}
}

void SubDriveBase::ResetGyroHeading(units::degree_t startingAngle) {
  _gyro.Reset();
  _gyro.SetAngleAdjustment(startingAngle.value());
}

frc::Pose2d SubDriveBase::GetPose() {return _poseEstimator.GetEstimatedPosition();}

void SubDriveBase::SetPose(frc::Pose2d pose) {
  auto fl = _frontLeft.GetPosition();
  auto fr = _frontRight.GetPosition();
  auto bl = _backLeft.GetPosition();
  auto br = _backRight.GetPosition();
  _poseEstimator.ResetPosition(GetHeading(), {fl, fr, bl, br}, pose);
}

void SubDriveBase::DisplayPose(std::string label, frc::Pose2d pose){
  _fieldDisplay.GetObject(label)->SetPose(pose);  
}

void SubDriveBase::UpdatePosition(frc::Pose2d robotPosition) {
  _poseEstimator.AddVisionMeasurement(robotPosition, 2_ms);
}

void SubDriveBase::DisplayTrajectory(std::string name, frc::Trajectory trajectory) {
  _fieldDisplay.GetObject(name)->SetTrajectory(trajectory);
}
  
void SubDriveBase::AddVisionMeasurement(frc::Pose2d pose, double ambiguity, units::second_t timeStamp){
  frc::SmartDashboard::PutNumber("Timestamp", timeStamp.value());
  _poseEstimator.AddVisionMeasurement(pose, timeStamp);
}

void SubDriveBase::SetNeutralMode(NeutralMode mode) {
  _frontLeft.SetNeutralMode(mode);
  _frontRight.SetNeutralMode(mode);
  _backLeft.SetNeutralMode(mode);
  _backRight.SetNeutralMode(mode);
}

units::degree_t SubDriveBase::GetPitch(){
  return _gyro.GetPitch() * 1_deg;
}