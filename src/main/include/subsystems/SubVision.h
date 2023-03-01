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
#include <photonlib/PhotonPoseEstimator.h>
#include <photonlib/SimPhotonCamera.h>
#include <photonlib/SimVisionSystem.h>
#include <photonlib/SimVisionTarget.h>
#include <frc/Filesystem.h>

struct Measurement {
  frc::Pose3d pose;
  units::second_t timeStamp;
  double ambiguity;
};

class SubVision : public frc2::SubsystemBase {
 public:
  SubVision();
  static SubVision& GetInstance() {
    static SubVision inst;
    return inst;
  }
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SimulationPeriodic() override;
  std::optional<photonlib::EstimatedRobotPose> GetMeasurement();

 private:
  std::string CAM_NAME = "arducam";

  // frc::Transform3d _camToBot{{-112_mm, 48_mm, -643_mm}, {}}; // limelight
  frc::Transform3d _camToBot{{-112_mm, 41_mm, -680_mm}, {}}; // arducam
  
  frc::AprilTagFieldLayout _tagLayout{frc::filesystem::GetDeployDirectory() + "/AprilTags.json"};

  photonlib::PhotonPoseEstimator _visionPoseEstimator{
      _tagLayout,
      photonlib::PoseStrategy::MULTI_TAG_PNP,
      photonlib::PhotonCamera{CAM_NAME},
      _camToBot.Inverse()};

  photonlib::SimVisionSystem _visionSim{CAM_NAME, 45_deg, _camToBot, 15_m,
                                        360,         240,    0.0001};
};
