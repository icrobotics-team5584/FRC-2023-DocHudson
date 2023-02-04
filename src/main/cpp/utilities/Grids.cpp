#include "utilities/Grids.h"
#include <map>
#include <units/length.h>
#include <units/angle.h>

namespace grids {
    std::map <DrivePose, frc::Pose2d> ScoringLocations = {
        {{Grid::Left, Column::Left}, {14.74_m, 5.02_m, 0_deg}}, 
        {{Grid::Left, Column::Middle}, {14.74_m, 4.43_m, 0_deg}}, 
        {{Grid::Left, Column::Right}, {14.74_m, 3.82_m, 0_deg}}, 
        {{Grid::Middle, Column::Left}, {14.74_m, 3.25_m, 0_deg}}, 
        {{Grid::Middle, Column::Middle}, {14.74_m, 2.73_m, 0_deg}}, 
        {{Grid::Middle, Column::Right}, {14.74_m, 2.16_m, 0_deg}},
        {{Grid::Right, Column::Left}, {14.74_m, 1.59_m, 0_deg}}, 
        {{Grid::Right, Column::Middle}, {14.74_m, 1.06_m, 0_deg}}, 
        {{Grid::Right, Column::Right}, {14.74_m, 0.43_m, 0_deg}} 
        
        
    };
}
