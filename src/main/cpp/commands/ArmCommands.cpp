#include "commands/ArmCommands.h"
#include "subsystems/SubArm.h"
#include "units/length.h"
#include "RobotContainer.h"
#include "subsystems/SubIntake.h"

namespace cmd{
    using namespace frc2::cmd;

    frc2::CommandPtr ArmToHighCone(){return ArmToPos(133_cm, 105_cm);} 
    frc2::CommandPtr ArmToMidCone(){return ArmToPos(110_cm,92_cm);} //gtg

    frc2::CommandPtr ArmToHighCube(){return ArmToPos(100_cm, 97_cm);} 
    frc2::CommandPtr ArmToMidCube(){return ArmToPos(58_cm, 67_cm);}

    frc2::CommandPtr ArmToLowCubeOrCone() {return ArmToPos(45_cm, 15_cm);}
    frc2::CommandPtr ArmToLoadingStation(){return ArmToPos(45_cm, 100_cm);}
	frc2::CommandPtr ArmToDefaultLocation(){return ArmToPos(70_cm, 40_cm);} //gtg

    frc2::CommandPtr PickUpCube(){return ArmToPos(90_cm, 14_cm);} //gtg
    frc2::CommandPtr PickUpUprightCone(){return ArmToPos(80_cm, 17_cm);} //gtg
    frc2::CommandPtr PickUpSlantedCone(){return ArmToPos(90_cm, -5_cm);} //gtg

    frc2::CommandPtr CubeConeSwitch(){
        return RunOnce([]{
            if(RobotContainer::isConeMode){RobotContainer::isConeMode = false;}
            else{RobotContainer::isConeMode = true;}
        });
    }
    
    frc2::CommandPtr ArmToHigh(){
        return Either(ArmToHighCone(), ArmToHighCube(), []{return RobotContainer::isConeMode;});
    }

    frc2::CommandPtr ArmToMid(){
        return Either(ArmToMidCone(), ArmToMidCube(), []{return RobotContainer::isConeMode;});
    }

    frc2::CommandPtr ArmPickUp(){
        return Either( PickUpCone(), PickUpCube(), []{return RobotContainer::isConeMode;});
    }

    frc2::CommandPtr PickUpCone(){
        return Either( PickUpUprightCone(), PickUpSlantedCone(), []{return SubIntake::GetInstance().SensesCone();});
    }

    frc2::CommandPtr ArmToPos(auto x, auto y) {
        return RunOnce([x,y] () { SubArm::GetInstance().ArmPos(x,y); }).AndThen(WaitUntil([] () { return SubArm::GetInstance().CheckPosition(); }));
    }
}