#include "commands/GamePieceCommands.h"
#include "subsystems/SubClaw.h"
#include "subsystems/SubIntake.h"
#include "RobotContainer.h"
#include "commands/ArmCommands.h"

namespace cmd {
using namespace frc2::cmd;

frc2::CommandPtr ClawExpand() {
  return RunOnce([] { SubClaw::GetInstance().ClawUnclamped(); });
}

frc2::CommandPtr ClawRetract() {
  return ClawExpand();
}

frc2::CommandPtr ClawGrabCone() {
  return RunOnce([] { SubClaw::GetInstance().ClawClampedCone(); });
}

frc2::CommandPtr ClawGrabCube() {
  return RunOnce([] { SubClaw::GetInstance().ClawClampedCube(); });
}

frc2::CommandPtr ClawToggle() {
  return Either(ClawClose(), ClawExpand(),
                [] { return SubClaw::GetInstance().IsTryingToUnclamp(); });
}

frc2::CommandPtr Intake() {
  return ClawGrabCone().AndThen(ArmPickUp())
      .AlongWith(DeployIntake().AndThen(ClawExpand()));
}

frc2::CommandPtr DeployIntake(){
  return RunOnce([] {
           SubIntake::GetInstance().DeployIntake();
           SubIntake::GetInstance().IntakeLeft();
           SubIntake::GetInstance().IntakeRight();
         }).AndThen(WaitUntil( [] { return SubIntake::GetInstance().CheckReach();}));
}

frc2::CommandPtr StowGamePiece() {
  return RunOnce([] { SubIntake::GetInstance().RetractIntake(); })
      .AndThen(ArmToDefaultLocation());
}

frc2::CommandPtr StartIntake() {
  return RunOnce([] {
    SubIntake::GetInstance().IntakeLeft();
    SubIntake::GetInstance().IntakeRight();
  });
}

frc2::CommandPtr StopIntake() {
  return RunOnce([] { SubIntake::GetInstance().Stop(); });
}

frc2::CommandPtr Outtake() {
  return StartEnd(
      [] {
        SubIntake::GetInstance().DeployIntake();
        SubIntake::GetInstance().OuttakeLeft();
        SubIntake::GetInstance().OuttakeRight();
      },
      [] {
        SubIntake::GetInstance().Stop();
      });
}

frc2::CommandPtr StartOuttake() {
  return RunOnce([] {
    SubIntake::GetInstance().OuttakeLeft();
    SubIntake::GetInstance().OuttakeRight();
  });
}

frc2::CommandPtr StopOuttake() {
  return RunOnce([] { SubIntake::GetInstance().Stop(); });
}

frc2::CommandPtr ClawClose() {
  return Either(ClawGrabCone(), ClawGrabCube(),
                [] { return RobotContainer::isConeMode; });
}

frc2::CommandPtr ClawOpen() {
  return ClawExpand();
}

frc2::CommandPtr DriveIntakeToSwitch() {
  return StartEnd([] { SubIntake::GetInstance().DriveDeployMotor(0.3); },
                  [] { SubIntake::GetInstance().DriveDeployMotor(0); })
      .Until([] { return SubIntake::GetInstance().LocatingSwitchIsHit(); });
}

}  // namespace cmd
