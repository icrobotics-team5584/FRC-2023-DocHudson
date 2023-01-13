#include "commands/ArmCommands.h"
#include "subsystems/SubArm.h"
#include "units/length.h"

namespace cmd{
    using namespace frc2::cmd;

    //ARM_ROOT_X = 0.05m

    frc2::CommandPtr ArmToHighCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.99156774_m + SubArm::ARM_ROOT_X, 1.1668125_m + 0.07_m);});}
    frc2::CommandPtr ArmToMidCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.559435_m + SubArm::ARM_ROOT_X, 0.862787_m + 0.07_m);});}

    frc2::CommandPtr ArmToHighCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.2017795_m + 0.8024369_m + SubArm::ARM_ROOT_X, 0.97_m);});}
    frc2::CommandPtr ArmToMidCube(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.222655_m + 0.35724_m + SubArm::ARM_ROOT_X, 0.67_m);});}

    frc2::CommandPtr ArmToLowCubeOrCone(){return RunOnce([]{SubArm::GetInstance().ArmPos(0.17862_m + SubArm::ARM_ROOT_X, 0.07_m);});}
    frc2::CommandPtr ArmToLoadingStation(){return RunOnce([]{SubArm::GetInstance().ArmPos(SubArm::ARM_ROOT_X, 0.942992018_m);});}

}