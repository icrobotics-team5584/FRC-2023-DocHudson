// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubVision.h"
#include "subsystems/SubDriveBase.h"
#include <fmt/format.h>


SubVision::SubVision() {
     for (int i=0; i<=8; i++) {
    auto pose = _tagLayout->GetTagPose(i);
    if (pose.has_value()) {
      photonlib::SimVisionTarget simTag{pose.value(), 8_in, 8_in, i};
      _visionSim.AddSimVisionTarget(simTag);
     SubDriveBase::GetInstance().DisplayPose(fmt::format("tag{}", i), pose.value().ToPose2d());
    }
  }
  }

std::optional <std::pair<frc::Pose3d, units::second_t>> SubVision::GetMeasurement(){
if (_camera->GetLatestResult().HasTargets()) {
  return std::optional{_visionPoseEstimator.Update()};
} else {return {};}
};
// This method will be called once per scheduler run
void SubVision::Periodic() {
    void UpdateOdometry();
}

void SubVision::SimulationPeriodic() {
  _visionSim.ProcessFrame(SubDriveBase::GetInstance().GetPose());
}
