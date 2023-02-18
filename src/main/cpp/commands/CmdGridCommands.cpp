// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdGridCommands.h"
#include "commands/DriveCommands.h"
#include "commands/GamePieceCommands.h"
#include "commands/ArmCommands.h"
#include <frc/geometry/Translation2d.h>
#include "RobotContainer.h"
#include <frc/DriverStation.h>
#include "subsystems/SubDriveBase.h"

/*

grid layout


drive number blue             01 02 03     04 05 06     07 08 09

                     low -->  11 12 13     21 22 23     31 32 33
                     mid -->  14 15 16     24 25 26     34 35 36
                     hig -->  17 18 19     27 28 29     37 38 39
          ------------------------------------------------------------
                    DStation1       DStation2       DStation3
*/

namespace cmd {
using namespace frc2::cmd;

frc2::CommandPtr Score(grids::Column column, grids::Height height) {
  return DriveToPose([column] {
           auto alliance = frc::DriverStation::GetAlliance();
           if (RobotContainer::GridSelect == grids::Grid::Neutral ||
               alliance == frc::DriverStation::kInvalid) {
             return SubDriveBase::GetInstance().GetPose();
           }
           grids::DrivePose drivePose{RobotContainer::GridSelect, column};
           if (alliance == frc::DriverStation::kRed) {
             return grids::ScoringLocationsRed[drivePose];
           } else if (alliance == frc::DriverStation::kBlue) {
             return grids::ScoringLocationsBlue[drivePose];
           }
           return SubDriveBase::GetInstance().GetPose();
         })
      .AlongWith(ArmToScoringHeight(height))
      .AndThen(ClawExpand());
}
}  // namespace cmd
   // namespace cmd