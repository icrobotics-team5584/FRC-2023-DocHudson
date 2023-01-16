// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <photonlib/PhotonCamera.h>
#include <units/length.h>
#include <units/angle.h>
#include <frc/apriltag/AprilTagFieldLayout.h>
#include <frc/apriltag/AprilTagFields.h>
#include <map>
#include <photonlib/RobotPoseEstimator.h>
#include <photonlib/SimPhotonCamera.h>
#include <photonlib/SimVisionSystem.h>
#include <photonlib/SimVisionTarget.h>
#include <frc/Filesystem.h>

struct Measurement {
  frc::Pose3d pose;
  units::second_t latency;
  double ambiguity;
};

class SubVision : public frc2::SubsystemBase {
 public:
  SubVision();
  static SubVision &GetInstance() {static SubVision inst; return inst;}
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SimulationPeriodic() override;
  std::optional <Measurement> GetMeasurement();
 private:

std::shared_ptr<photonlib::PhotonCamera> _camera{new photonlib::PhotonCamera{"limelight"}};
  const units::meter_t CAMERA_HEIGHT = 665_mil;
  const units::degree_t CAMERA_PITCH = 2_deg;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  frc::Transform3d _camToBot{{11_cm, 10_cm, 65.5_cm}, {}};

  std::shared_ptr<frc::AprilTagFieldLayout> _tagLayout{new frc::AprilTagFieldLayout{frc::filesystem::GetDeployDirectory()+"/AprilTags.json"}};

  photonlib::RobotPoseEstimator _visionPoseEstimator{
    _tagLayout, 
  photonlib::PoseStrategy::LOWEST_AMBIGUITY,
  {{_camera, _camToBot}}
};

photonlib::SimVisionSystem _visionSim{"limelight", 45_deg, _camToBot, 15_m, 360, 240, 0.0001};

};
