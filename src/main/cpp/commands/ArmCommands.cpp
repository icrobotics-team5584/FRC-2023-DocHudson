#include "commands/ArmCommands.h"
#include "subsystems/SubArm.h"
#include "units/length.h"
#include "RobotContainer.h"
#include "subsystems/SubIntake.h"

namespace cmd{
    using namespace frc2::cmd;

    //ARM_ROOT_X = 0.05m

    frc2::CommandPtr ArmToHighCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(1400_mm, 1150_mm-200_mm);});}
    frc2::CommandPtr ArmToMidCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(980_mm, 940_mm);});}

    frc2::CommandPtr ArmToHighCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.2017795_m + 0.8024369_m + SubArm::ARM_ROOT_X, 0.97_m);});}
    frc2::CommandPtr ArmToMidCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.222655_m + 0.35724_m + SubArm::ARM_ROOT_X, 0.67_m);});}

    frc2::CommandPtr ArmToLowCubeOrCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.17862_m + SubArm::ARM_ROOT_X, 0.07_m);});}
    frc2::CommandPtr ArmToLoadingStation(){return RunOnce([]{SubArm::GetInstance().ArmPos(SubArm::ARM_ROOT_X, 0.942992018_m);});}

    frc2::CommandPtr PickUpCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(52_cm, 7_cm);});}
    frc2::CommandPtr PickUpUprightCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(52_cm, 33_cm);});}
    frc2::CommandPtr PickUpSlantedCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(52_cm, 3_cm);});}

    frc2::CommandPtr CubeConeSwitch(){
        return RunOnce([]{
            if(RobotContainer::isConeMode){RobotContainer::isConeMode = false;}
            else{RobotContainer::isConeMode = true;}
        });
    }
    
    frc2::CommandPtr ArmToHigh(){
        return Either(
            ArmToHighCone(),
            ArmToHighCube(),
            []{return RobotContainer::isConeMode;}
        );
    }

    frc2::CommandPtr ArmToMid(){
        return Either(
            ArmToMidCone(),
            ArmToMidCube(),
            []{return RobotContainer::isConeMode;}
        );
    }

    frc2::CommandPtr ArmPickUp(){
        return Either(
            PickUpCone(),
            PickUpCube(),
            []{return RobotContainer::isConeMode;}
        );
    }

    frc2::CommandPtr PickUpCone(){
        return Either(
            PickUpUprightCone(),
            PickUpSlantedCone(),
            []{return SubIntake::GetInstance().SensesCone();} // substitute for line breaker
        );
    }

}