#pragma once

#include <map>
#include <frc/geometry/Pose2d.h>

namespace grids {

enum class Grid { Neutral, Left, Middle, Right };
enum class Column { Left, Middle, Right };
enum class Height { High, Middle, Low };

struct DrivePose {
  Grid grid;
  Column column;

  auto operator<=>(const DrivePose& other) const = default;
};

extern std::map<DrivePose, frc::Pose2d> ScoringLocationsBlue;
extern std::map<DrivePose, frc::Pose2d> ScoringLocationsRed;
}  // namespace grids
