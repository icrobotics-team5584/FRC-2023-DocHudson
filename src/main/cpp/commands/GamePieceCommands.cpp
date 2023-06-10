#include "commands/GamePieceCommands.h"
#include "RobotContainer.h"
#include "commands/ArmCommands.h"
#include "subsystems/SubRollerIntake.h"

namespace cmd {
using namespace frc2::cmd;

frc2::CommandPtr RollerOuttake(){
  return StartEnd([]{SubRollerIntake::GetInstance().RollerOuttake();},
                  []{SubRollerIntake::GetInstance().StopRollerIntake();}
  );
}

frc2::CommandPtr StartRollerIntake(){
  return RunOnce([]{SubRollerIntake::GetInstance().RollerIntake();});
}

frc2::CommandPtr StopRollerIntake(){
  return RunOnce([]{SubRollerIntake::GetInstance().StopRollerIntake();});
}

frc2::CommandPtr StartRollerOuttake(){
  return RunOnce([]{SubRollerIntake::GetInstance().RollerOuttake();});
}

frc2::CommandPtr RollerIntake() {
  return StartEnd([] { SubRollerIntake::GetInstance().RollerIntake(); },
                  [] { SubRollerIntake::GetInstance().IdleRollerIntake(); })
      .Until([] { return SubRollerIntake::GetInstance().GamePieceDetected(); });
}

frc2::CommandPtr RollerIntakeWithRumble(
    frc2::CommandXboxController& controller1,
    frc2::CommandXboxController& controller2) {
  return RollerIntake()
      .AndThen([&] {
        controller1.SetRumble(frc::GenericHID::kBothRumble, 1);
        controller2.SetRumble(frc::GenericHID::kBothRumble, 1);
      })
      .AndThen(Wait(0.2_s))
      .FinallyDo([&](bool _) {
        controller1.SetRumble(frc::GenericHID::kBothRumble, 0);
        controller2.SetRumble(frc::GenericHID::kBothRumble, 0);
      });
}

frc2::CommandPtr StopRollerOuttake(){
  return RunOnce([]{SubRollerIntake::GetInstance().StopRollerIntake();});
}

}  