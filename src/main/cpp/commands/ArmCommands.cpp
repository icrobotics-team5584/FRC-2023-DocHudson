#include "commands/ArmCommands.h"
#include "subsystems/SubArm.h"
#include "units/length.h"
#include "RobotContainer.h"
#include "subsystems/SubIntake.h"

namespace cmd{
    using namespace frc2::cmd;

    frc2::CommandPtr ArmToHighCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(133_cm, 105_cm);});}  
    frc2::CommandPtr ArmToMidCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(110_cm, 92_cm);});} //gtg

    frc2::CommandPtr ArmToHighCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(100_cm, 97_cm);});} 
    frc2::CommandPtr ArmToMidCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(58_cm, 67_cm);});}

    frc2::CommandPtr ArmToLowCubeOrCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(45_cm, 15_cm);});}
    frc2::CommandPtr ArmToLoadingStation(){return RunOnce([]{SubArm::GetInstance().ArmPos(45_cm, 100_cm);});}
	  frc2::CommandPtr ArmToDefaultLocation(){return RunOnce([]{SubArm::GetInstance().ArmPos(70_cm, 40_cm);});} //gtg

    frc2::CommandPtr PickUpCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(90_cm, 14_cm);});} //gtg
    frc2::CommandPtr PickUpUprightCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(80_cm, 17_cm);});} //gtg
    frc2::CommandPtr PickUpSlantedCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(90_cm, -5_cm);});} //gtg

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

    

}