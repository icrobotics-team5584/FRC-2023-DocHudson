#pragma once

#include <map>
#include <frc/geometry/Pose2d.h>

namespace grids {

enum class Grid { LS, Left, Middle, Right, Neutral};
enum class Column { Left, Middle, Right};
enum class Height { High, Middle, Low, LS};

struct DrivePose {
  Grid grid;
  Column column;

  auto operator<=>(const DrivePose& other) const = default;
};

extern std::map<DrivePose, frc::Pose2d> ScoringLocationsBlue;
extern std::map<DrivePose, frc::Pose2d> ScoringLocationsRed;
}  // namespace grids
