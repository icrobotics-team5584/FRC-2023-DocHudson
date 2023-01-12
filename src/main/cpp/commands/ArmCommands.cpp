// #include "commands/ArmCommands.h"
// #include "subsystems/SubArm.h"
// #include "units/length.h"

// namespace cmd{
//     using namespace frc2::cmd;

//     frc2::CommandPtr highCone() {
//         return RunOnce([]{SubArm::GetInstance().DriveTo(0.99156774_m + SubArm::ARM_ROOT_X, 1.1668125_m + 0.07_m);});
//     }
// }

/*
_driverController.A().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(20_deg, -20_deg);}));
_driverController.B().OnTrue(RunOnce([]{SubArm::GetInstance().DriveTo(10_deg, 10_deg);}));
//ARM_LENGTH = 1m, ARM_LENGTH_2 = 1m
_driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.17862_m + SubArm::ARM_ROOT_X, 0.07_m);})); //Cube/Cone low
_driverController.Y().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.222655_m + 0.35724_m + SubArm::ARM_ROOT_X, 0.67_m);})); //Cube mid
//_driverController.X().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.2017795_m + 0.8024369_m + SubArm::ARM_ROOT_X, 0.97_m);})); //Cube high
_driverController.LeftBumper().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.559435_m + SubArm::ARM_ROOT_X, 0.862787_m + 0.07_m);})); //Cone mid
_driverController.RightBumper().OnTrue(RunOnce([]{SubArm::GetInstance().ArmPos(0.99156774_m + SubArm::ARM_ROOT_X, 1.1668125_m + 0.07_m);})); //Cone high
*/