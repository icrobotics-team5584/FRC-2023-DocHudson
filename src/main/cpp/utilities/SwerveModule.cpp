// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "utilities/SwerveModule.h"
#include "utilities/Conversion.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/MathUtil.h>
#include <frc/RobotBase.h>

SwerveModule::SwerveModule(int canDriveMotorID, int canTurnMotorID,
                           int canTurnEncoderID, double cancoderMagOffset)
    : _canDriveMotor(canDriveMotorID, "Canivore"),
      _canTurnMotor(canTurnMotorID, "Canivore"),
      _canTurnEncoder(canTurnEncoderID, "Canivore") {
  // Config CANCoder
  _canTurnEncoder.ConfigFactoryDefault();
  _canTurnEncoder.SetPositionToAbsolute();
  _canTurnEncoder.ConfigAbsoluteSensorRange(AbsoluteSensorRange::Signed_PlusMinus180);
  _canTurnEncoder.ConfigMagnetOffset(cancoderMagOffset);

  // Config Turning Motor
  _canTurnMotor.ConfigFactoryDefault();
  _canTurnMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
  _canTurnMotor.ConfigFeedbackNotContinuous(true);
  _canTurnMotor.Config_kP(PID_SLOT_INDEX, TURN_P);
  _canTurnMotor.Config_kI(PID_SLOT_INDEX, TURN_I);
  _canTurnMotor.Config_kD(PID_SLOT_INDEX, TURN_D);
  _canTurnMotor.ConfigSupplyCurrentLimit(CURRENT_LIMIT_CONFIG);
  _canTurnMotor.SetInverted(true); // make counter clockwise rotations positive
  _canTurnMotor.SetNeutralMode(NeutralMode::Brake);

  // Config Driving Motor
  _canDriveMotor.ConfigFactoryDefault();
  _canDriveMotor.ConfigSelectedFeedbackSensor(FeedbackDevice::IntegratedSensor);
  _canDriveMotor.Config_kP(PID_SLOT_INDEX, DRIVE_P);
  _canDriveMotor.Config_kI(PID_SLOT_INDEX, DRIVE_I);
  _canDriveMotor.Config_kD(PID_SLOT_INDEX, DRIVE_D);
  _canDriveMotor.Config_kF(PID_SLOT_INDEX, DRIVE_F);
  _canDriveMotor.ConfigSupplyCurrentLimit(CURRENT_LIMIT_CONFIG);
  _canDriveMotor.SetNeutralMode(NeutralMode::Brake);
}

void SwerveModule::SetDesiredState(const frc::SwerveModuleState& referenceState) {
  // Optimize the reference state to avoid spinning further than 90 degrees
  auto targetState = frc::SwerveModuleState::Optimize(referenceState, GetAngle());

  // Move target angle so we can cross over the 180 degree line without going the long way round
  auto difference = targetState.angle.Degrees() - GetAngle().Degrees();
  difference = frc::InputModulus(difference, -180_deg, 180_deg);
  auto targetAngle = GetAngle().Degrees() + difference;

  // Drive! These functions do some conversions and send targets to falcons
  SetDesiredAngle(targetAngle);
  SetDesiredVelocity(targetState.speed);
}

frc::SwerveModulePosition SwerveModule::GetPosition() {
  if (frc::RobotBase::IsSimulation()) {
    return {_simulatorDistanceTravelled, GetAngle().Radians()};
  }
  else {
    return {Conversions::FalconTicsToMeters(_canDriveMotor.GetSelectedSensorPosition(), DRIVE_GEAR_RATIO, WHEEL_RADIUS),
           GetAngle().Radians()};
  }
}

void SwerveModule::SendSensorsToDash() {
  std::string driveMotorName = "drive motor " + std::to_string(_canDriveMotor.GetDeviceID());
  std::string turnMotorName = "turn motor " + std::to_string(_canTurnMotor.GetDeviceID());
  std::string turnEncoderName = "turn encoder " + std::to_string(_canTurnEncoder.GetDeviceNumber());

  frc::SmartDashboard::PutNumber(driveMotorName + " velocity", _canDriveMotor.GetSelectedSensorVelocity());
  frc::SmartDashboard::PutNumber(turnMotorName  + " position degrees", GetAngle().Degrees().value());
  frc::SmartDashboard::PutNumber(turnMotorName  + " position tics", _canTurnMotor.GetSelectedSensorPosition());
  frc::SmartDashboard::PutNumber(turnMotorName  + " target", _canTurnMotor.GetClosedLoopTarget());
  frc::SmartDashboard::PutNumber(turnMotorName  + " error", _canTurnMotor.GetClosedLoopError());
  frc::SmartDashboard::PutNumber(turnEncoderName+ " Abs position", _canTurnEncoder.GetAbsolutePosition());
}

frc::Rotation2d SwerveModule::GetAngle() {
  // If in simulation, pretend swerve is always at target state
  const double rawPos = frc::RobotBase::IsReal()
                            ? _canTurnMotor.GetSelectedSensorPosition()
                            : _canTurnMotor.GetClosedLoopTarget();
  return Conversions::FalconTicsToOutputRotations(rawPos, TURNING_GEAR_RATIO);
}

units::meters_per_second_t SwerveModule::GetSpeed() {
  // If in simulation, pretend swerve is always at target state
  const double rawSpeed = frc::RobotBase::IsReal()
                            ? _canDriveMotor.GetSelectedSensorVelocity()
                            : _canDriveMotor.GetClosedLoopTarget();
  return Conversions::FalconVelToRobotVel(rawSpeed, DRIVE_GEAR_RATIO, WHEEL_RADIUS);
}

frc::SwerveModuleState SwerveModule::GetState() {
  return {GetSpeed(), GetAngle()};
}

void SwerveModule::SetDesiredAngle(units::degree_t angle) {
  const double targetRotations = angle.value() / 360.0;
  const int targetTics =  targetRotations * TICS_PER_TURNING_WHEEL_REVOLUTION;
  _canTurnMotor.Set(TalonFXControlMode::Position, targetTics);
}

void SwerveModule::SetDesiredVelocity(units::meters_per_second_t velocity) {
  double falconVel = Conversions::RobotVelToFalconVel(
      velocity, DRIVE_GEAR_RATIO, WHEEL_RADIUS);
  units::volt_t ffvolts = _feedFoward.Calculate(velocity);
  double ffpercent = ffvolts.value()/12;
  _canDriveMotor.Set(TalonFXControlMode::Velocity, falconVel,
                     DemandType::DemandType_ArbitraryFeedForward, ffpercent);
  _simulatorDistanceTravelled += velocity * 20_ms;
}

void SwerveModule::StopMotors() {
  _canDriveMotor.Set(TalonFXControlMode::PercentOutput, 0);
  _canTurnMotor.Set(TalonFXControlMode::PercentOutput, 0);
}

void SwerveModule::SetNeutralMode(NeutralMode mode) {
  _canTurnMotor.SetNeutralMode(mode);
  _canDriveMotor.SetNeutralMode(mode);
}

void SwerveModule::SyncSensors() {
  double cancoderDegrees = _canTurnEncoder.GetAbsolutePosition();
  double cancoderRevolutions = cancoderDegrees/360;
  int cancoderPosInFalconTics = cancoderRevolutions*TICS_PER_TURNING_WHEEL_REVOLUTION;
  _canTurnMotor.SetSelectedSensorPosition(cancoderPosInFalconTics);
}
