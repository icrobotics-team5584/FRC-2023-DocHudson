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
#include <frc/smartdashboard/Mechanism2d.h>
#include <frc/smartdashboard/MechanismLigament2d.h>
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
  void ArmPos(units::meter_t x, units::meter_t y);
  void CubeConeSwitch();

  static constexpr units::meter_t ARM_ROOT_X = 0.05_m;

 private:
  // motors
  ICSparkMax<> _armMotor1{21};
  ICSparkMax<> _armMotor2{20};
  ICSparkMax<> _armMotor1Follow{22};

  //arm 1
  static constexpr double P = 0.0;
  static constexpr double I = 0.0;
  static constexpr double D = 0.0;
  static constexpr double F = 0.01;
  
  static constexpr double GEAR_RATIO = 210.0; // only sim
  static constexpr units::kilogram_t ARM_MASS_1 = 1_kg; // only sim
  static constexpr units::degrees_per_second_t MAX_VEL = 20_deg_per_s;
  static constexpr units::degrees_per_second_squared_t MAX_ACCEL = 90_deg_per_s_sq;
  static constexpr units::degree_t TOLERANCE = 0.5_deg; 
  static constexpr units::meter_t ARM_LENGTH = 0.85_m;
  // static constexpr units::kilogram_square_meter_t MOI = 1_kg_sq_m; // only sim
  static constexpr units::degree_t MIN_ANGLE = -180_deg; // only sim
  static constexpr units::degree_t MAX_ANGLE = 180_deg; // only sim

  //arm 2
  static constexpr double P_2 = 0.0;
  static constexpr double I_2 = 0.0;
  static constexpr double D_2 = 0.0;
  static constexpr double F_2 = 0.0;
  
  static constexpr double GEAR_RATIO_2 = 165.0; // only sim
  static constexpr units::kilogram_t ARM_MASS_2 = 1_kg; // only sim
  static constexpr units::degrees_per_second_t MAX_VEL_2 = 20_deg_per_s;
  static constexpr units::degrees_per_second_squared_t MAX_ACCEL_2 = 90_deg_per_s_sq;
  static constexpr units::degree_t TOLERANCE_2 = 0.5_deg;
  static constexpr units::meter_t ARM_LENGTH_2 = 0.85_m;
  // static constexpr units::kilogram_square_meter_t MOI_2 = 1_kg_sq_m; // only sim
  static constexpr units::degree_t MIN_ANGLE_2 = -180_deg; // only sim
  static constexpr units::degree_t MAX_ANGLE_2 = 180_deg; // only sim

  // simulation of armMotor1
  frc::sim::SingleJointedArmSim _armSim{
    frc::DCMotor::NEO(2),
    GEAR_RATIO, 
    frc::sim::SingleJointedArmSim::EstimateMOI(ARM_LENGTH, ARM_MASS_1),
    ARM_LENGTH,
    MIN_ANGLE,
    MAX_ANGLE,
    ARM_MASS_1,
    false,
  };

  // simulation of armMotor2
  frc::sim::SingleJointedArmSim _armSim2{
    frc::DCMotor::NEO(2),
    GEAR_RATIO_2, 
    frc::sim::SingleJointedArmSim::EstimateMOI(ARM_LENGTH_2, ARM_MASS_2),
    ARM_LENGTH_2,
    MIN_ANGLE_2,
    MAX_ANGLE_2,
    ARM_MASS_2,
    false,
  };

  // Display of arm sim
  frc::Mechanism2d _doubleJointedArmMech{3, 3}; //canvas width and height
  frc::MechanismRoot2d* _root = _doubleJointedArmMech.GetRoot("armRoot", 2, 2); //root x and y
  frc::MechanismLigament2d* _arm1Ligament = _root->Append<frc::MechanismLigament2d>("ligament1", ARM_LENGTH.value(), 5_deg);
  frc::MechanismLigament2d* _arm2Ligament = _arm1Ligament->Append<frc::MechanismLigament2d>("ligament2", ARM_LENGTH.value(), 5_deg);

};
