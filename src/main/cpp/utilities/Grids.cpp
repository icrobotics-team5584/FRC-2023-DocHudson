#include "utilities/Grids.h"
#include <map>
#include <units/length.h>
#include <units/angle.h>

namespace grids {
    std::map <DrivePose, frc::Pose2d> ScoringLocations = {
        {{Grid::Left, Column::Left}, {{1_m, 4_m}, 45_deg}}, 
        {{Grid::Left, Column::Middle}, {1, 4}}, 
        {{Grid::Left, Column::Right}, {1, 4}}, 
        {{Grid::Middle, Column::Left}, {1, 4}}, 
        {{Grid::Middle, Column::Middle}, {1, 4}}, 
        {{Grid::Middle, Column::Right}, {1, 4}}, 
        {{Grid::Right, Column::Left}, {1, 4}}, 
        {{Grid::Right, Column::Middle}, {1, 4}}, 
        {{Grid::Right, Column::Right}, {1, 4}} 
        
        
    };
}
