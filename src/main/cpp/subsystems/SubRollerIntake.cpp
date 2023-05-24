// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubRollerIntake.h"
#include "RobotContainer.h"
#include <frc2/command/commands.h>
#include <frc2/command/button/Trigger.h>
#include <frc/smartdashboard/SmartDashboard.h>

SubRollerIntake::SubRollerIntake(){
    frc::SmartDashboard::PutData("Rol lerIntake/Left side motor", (wpi::Sendable*)&_rollerMotor);

    _rollerMotor.SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
}


void SubRollerIntake::RollerIntake(){
    _rollerMotor.Set(1);
}
void SubRollerIntake::RollerOuttake(){
    _rollerMotor.Set(-1);
}
void SubRollerIntake::StopRollerIntake(){
    _rollerMotor.Set(0);
}
void SubRollerIntake::IdleRollerIntake(){
    _rollerMotor.Set(0.1);
}
bool SubRollerIntake::GamePieceDetected() {
    if(_rollerMotor.GetVelocity() < 0.1_tps && _rollerMotor.Get() != 0) {
        return true;
    } else {return false;};
}

// This method will be called once per scheduler run
void SubRollerIntake::Periodic() {}

