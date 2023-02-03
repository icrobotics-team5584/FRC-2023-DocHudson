#pragma once
#include <map>
#include <frc/geometry/Pose2d.h>

namespace grids
{

enum Grid{Neutral, Left, Middle, Right};
enum Column{Left, Middle, Right};

struct DrivePose
{
   Grid grid; 
   Column column;
};

std::map <DrivePose, frc::Pose2d> ScoringLocations;
}
