#include "utilities/Grids.h"
#include <map>
#include <units/length.h>
#include <units/angle.h>

namespace grids {
    std::map <DrivePose, frc::Pose2d> ScoringLocationsRed = {
        {{Grid::Right, Column::Right}, {14.55_m, 4.95_m, 0_deg}},
        {{Grid::Right, Column::Middle}, {14.55_m, 4.43_m, 0_deg}}, 
        {{Grid::Right, Column::Left}, {14.55_m, 3.82_m, 0_deg}}, 
        {{Grid::Middle, Column::Right}, {14.55_m, 3.25_m, 0_deg}}, 
        {{Grid::Middle, Column::Middle}, {14.55_m, 2.73_m, 0_deg}}, 
        {{Grid::Middle, Column::Left}, {14.55_m, 2.16_m, 0_deg}},
        {{Grid::Left, Column::Right}, {14.55_m, 1.59_m, 0_deg}}, 
        {{Grid::Left, Column::Middle}, {14.55_m, 1.06_m, 0_deg}}, 
        {{Grid::Left, Column::Left}, {14.55_m, 0.43_m, 0_deg}},
        {{Grid::LS, Column::Left}, {0.68_m, 7.47_m, 180_deg}},
        {{Grid::LS, Column::Right}, {0.68_m, 6.15_m, 180_deg}},
        
        
    };

    std::map <DrivePose, frc::Pose2d> ScoringLocationsBlue = {
        {{Grid::Left, Column::Left}, {1.84_m, 5.02_m, 180_deg}},
        {{Grid::Left, Column::Middle}, {1.84_m, 4.43_m, 180_deg}}, 
        {{Grid::Left, Column::Right}, {1.84_m, 3.82_m, 180_deg}}, 
        {{Grid::Middle, Column::Left}, {1.84_m, 3.25_m, 180_deg}}, 
        {{Grid::Middle, Column::Middle}, {1.84_m, 2.73_m, 180_deg}}, 
        {{Grid::Middle, Column::Right}, {1.84_m, 2.16_m, 180_deg}},
        {{Grid::Right, Column::Left}, {1.84_m, 1.59_m, 180_deg}}, 
        {{Grid::Right, Column::Middle}, {1.84_m, 1.06_m, 180_deg}}, 
        {{Grid::Right, Column::Right}, {1.84_m, 0.43_m, 180_deg}},
        {{Grid::LS, Column::Right}, {15.8_m, 5.96_m, 0_deg}},
        {{Grid::LS, Column::Left}, {15.8_m, 7.33_m, 0_deg}}
        
        
        
    };
}
