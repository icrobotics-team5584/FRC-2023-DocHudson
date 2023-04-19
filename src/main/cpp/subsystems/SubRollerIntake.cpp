// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubRollerIntake.h"
#include "RobotContainer.h"
#include <frc2/command/commands.h>
#include <frc2/command/button/Trigger.h>
#include <frc/smartdashboard/SmartDashboard.h>

SubRollerIntake::SubRollerIntake(){
    frc::SmartDashboard::PutData("RollerIntake/Right side current", (wpi::Sendable*)&_leftMotor);
    frc::SmartDashboard::PutData("RollerIntake/Left side current", (wpi::Sendable*)&_leftMotor);

    _leftMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    _rightMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}


void SubRollerIntake::RollerIntake(){
    _leftMotor.Set(0.3);
    _rightMotor.Set(-0.3);
}
void SubRollerIntake::RollerOuttake(){
    _leftMotor.Set(-0.3);
    _rightMotor.Set(0.3);
}
void SubRollerIntake::StopRollerIntake(){
    _leftMotor.Set(0);
    _rightMotor.Set(0);
}
void SubRollerIntake::IdleRollerIntake(){
    _leftMotor.Set(0.1);
    _rightMotor.Set(-0.1);
}

// This method will be called once per scheduler run
void SubRollerIntake::Periodic() {}

