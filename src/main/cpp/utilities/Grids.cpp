#include "utilities/Grids.h"
#include <map>
#include <units/length.h>
#include <units/angle.h>

namespace grids {
    std::map <DrivePose, frc::Pose2d> ScoringLocations = {
        {{Grid::Left, Column::Left}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Left, Column::Middle}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Left, Column::Right}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Middle, Column::Left}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Middle, Column::Middle}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Middle, Column::Right}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Right, Column::Left}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Right, Column::Middle}, {1_m, 4_m, 45_deg}}, 
        {{Grid::Right, Column::Right}, {1_m, 4_m, 45_deg}} 
        
        
    };
}
