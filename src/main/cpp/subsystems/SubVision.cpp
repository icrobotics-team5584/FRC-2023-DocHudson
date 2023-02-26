// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubVision.h"
#include "subsystems/SubDriveBase.h"
#include <fmt/format.h>



SubVision::SubVision() {
  // _visionPoseEstimator.SetMultiTagFallbackStrategy(photonlib::LOWEST_AMBIGUITY);
  for (int i = 0; i <= 8; i++) {
    auto pose = _tagLayout.GetTagPose(i);
    if (pose.has_value()) {
      photonlib::SimVisionTarget simTag{pose.value(), 8_in, 8_in, i};
      _visionSim.AddSimVisionTarget(simTag);
     SubDriveBase::GetInstance().DisplayPose(fmt::format("tag{}", i), pose.value().ToPose2d());
    }
  }
}

std::optional<photonlib::EstimatedRobotPose> SubVision::GetMeasurement() {
    frc::SmartDashboard::PutNumber("Vision/Early timestamp", _visionPoseEstimator.GetCamera().GetLatestResult().GetLatency().value());
    return _visionPoseEstimator.Update();

}

// This method will be called once per scheduler run
void SubVision::Periodic() {

}

void SubVision::SimulationPeriodic() {
  _visionSim.ProcessFrame(SubDriveBase::GetInstance().GetPose());
}
