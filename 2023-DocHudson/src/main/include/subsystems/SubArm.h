// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <units/mass.h>
#include <units/angular_velocity.h>
#include <units/angular_acceleration.h>
#include <units/angle.h>
#include <frc/simulation/SingleJointedArmSim.h>
#include <frc/simulation/DIOSim.h> // sim limit switches
#include "utilities/ICSparkMax.h"

class SubArm : public frc2::SubsystemBase {
 public:

  //get arm subsytem
  static SubArm &GetInstance(){
    static SubArm inst;
    return inst;
  }

  SubArm();
  void Periodic() override;
  void SimulationPeriodic() override;
  void DriveTo(units::degree_t deg1, units::degree_t deg2);

 private:
  ICSparkMax<> _armMotor1{99};
  ICSparkMax<> _armMotor2{98};
  //arm 1
  static constexpr double P = 0.0;
  static constexpr double I = 0.0;
  static constexpr double D = 0.0;
  static constexpr double F = 0.0;
  
  static constexpr double GEAR_RATIO = 200.0;
  static constexpr units::kilogram_t ARM_MASS_1 = 6_kg;
  static constexpr units::degrees_per_second_t MAX_VEL = 90_deg_per_s;
  static constexpr units::degrees_per_second_squared_t MAX_ACCEL = 90_deg_per_s_sq;
  static constexpr units::degree_t TOLERANCE = 0.5_deg; 
  static constexpr units::meter_t ARM_LENGTH = 1_m;
  static constexpr units::kilogram_square_meter_t MOI = 0.01_kg_sq_m;
  static constexpr units::degree_t MIN_ANGLE = 0_deg;
  static constexpr units::degree_t MAX_ANGLE = 90_deg;

  //arm 2
  static constexpr double P_2 = 0.0;
  static constexpr double I_2 = 0.0;
  static constexpr double D_2 = 0.0;
  static constexpr double F_2 = 0.0;
  
  static constexpr double GEAR_RATIO_2 = 200.0;
  static constexpr units::kilogram_t ARM_MASS_2 = 6_kg;
  static constexpr units::degrees_per_second_t MAX_VEL_2 = 90_deg_per_s;
  static constexpr units::degrees_per_second_squared_t MAX_ACCEL_2 = 90_deg_per_s_sq;
  static constexpr units::degree_t TOLERANCE_2 = 0.5_deg;
  static constexpr units::meter_t ARM_LENGTH_2 = 1_m;
  static constexpr units::kilogram_square_meter_t MOI_2 = 0.01_kg_sq_m;
  static constexpr units::degree_t MIN_ANGLE_2 = 0_deg;
  static constexpr units::degree_t MAX_ANGLE_2 = 90_deg;
   


  // simulation of armMotor1
  frc::sim::SingleJointedArmSim _armSim{
    frc::DCMotor::NEO(2),
    GEAR_RATIO, 
    MOI,
    ARM_LENGTH,
    MIN_ANGLE,
    MAX_ANGLE,
    ARM_MASS_1,
    true,
  };
  // simulation of armMotor2
  frc::sim::SingleJointedArmSim _armSim2{
    frc::DCMotor::NEO(2),
    GEAR_RATIO_2, 
    MOI_2,
    ARM_LENGTH_2,
    MIN_ANGLE_2,
    MAX_ANGLE_2,
    ARM_MASS_2,
    true,
  };

};

