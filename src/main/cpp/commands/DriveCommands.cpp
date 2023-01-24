#include "commands/DriveCommands.h"
#include "subsystems/SubDriveBase.h"
#include "subsystems/SubVision.h"


namespace cmd {
    using namespace frc2::cmd;

    frc2::CommandPtr AddVisionMeasurement() {
        return Run([] {
            auto result = SubVision::GetInstance().GetMeasurement();
           if (result.has_value()) {
            auto [pose, latency, ambiguity] = result.value();
            SubDriveBase::GetInstance().AddVisionMeasurement(pose.ToPose2d(), ambiguity, latency);
           }
        }, {&SubVision::GetInstance()});
      
    }

    //Grid drive commands
    frc2::CommandPtr Drive11() {
        
    }

    frc2::CommandPtr Drive12() {
        
    }

    frc2::CommandPtr Drive13() {
        
    }

    frc2::CommandPtr Drive14() {
        
    }

    frc2::CommandPtr Drive15() {
        
    }

    frc2::CommandPtr Drive16() {
        
    }

    frc2::CommandPtr Drive17() {
        
    }

    frc2::CommandPtr Drive18() {
        
    }

    frc2::CommandPtr Drive19() {
        
    }
    
    frc2::CommandPtr Drive21() {
        
    }
    
    frc2::CommandPtr Drive22() {
        
    }
    
    frc2::CommandPtr Drive23() {
        
    }
    
    frc2::CommandPtr Drive24() {
        
    }
    
    frc2::CommandPtr Drive25() {
        
    }
    
    frc2::CommandPtr Drive26() {
        
    }
    
    frc2::CommandPtr Drive27() {
        
    }
    
    frc2::CommandPtr Drive28() {
        
    }
    
    frc2::CommandPtr Drive29() {
        
    }
    
    frc2::CommandPtr Drive31() {
        
    }
    
    frc2::CommandPtr Drive32() {
        
    }
    
    frc2::CommandPtr Drive33() {
        
    }
    
    frc2::CommandPtr Drive34() {
        
    }
    
    frc2::CommandPtr Drive35() {
        
    }
    
    frc2::CommandPtr Drive36() {
        
    }
    
    frc2::CommandPtr Drive37() {
        
    }
    
    frc2::CommandPtr Drive38() {
        
    }
    
    frc2::CommandPtr Drive39() {
        
    }
    
    
}



