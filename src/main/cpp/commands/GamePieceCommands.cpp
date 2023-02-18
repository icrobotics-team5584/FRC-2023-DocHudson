#include "commands/GamePieceCommands.h"
#include "subsystems/SubClaw.h"
#include "subsystems/SubIntake.h"
#include "RobotContainer.h"
#include "commands/ArmCommands.h"

namespace cmd {
    using namespace frc2::cmd;

    frc2::CommandPtr ClawExpand() {
        return RunOnce(
            [] {SubClaw::GetInstance().ClawUnclamped();}
        );
    }

    frc2::CommandPtr ClawRetract() {
        return RunOnce(
            [] {SubClaw::GetInstance().ClawClamped();}
        );
    }

    frc2::CommandPtr ClawGrabCone(){
        return ClawRetract();
    }

    frc2::CommandPtr ClawGrabCube(){
        return RunOnce(
        [] {
            SubClaw::GetInstance().ClawClamped();
        }
        );
    }

    frc2::CommandPtr Intake(){
        return StartEnd(
            [] {SubIntake::GetInstance().DeployIntake();
               SubIntake::GetInstance().IntakeLeft();
               SubIntake::GetInstance().IntakeRight();
               ArmPickUp();
               SubClaw::GetInstance().ClawClamped();},
            [] {SubIntake::GetInstance().Stop();}
        );
    }
    

    frc2::CommandPtr StowGamePiece() {
        return RunOnce([] {
            SubIntake::GetInstance().RetractIntake();
            ArmToDefaultLocation();
        });
    }    

    frc2::CommandPtr StartIntake() {
        return RunOnce (
            [] {SubIntake::GetInstance().IntakeLeft();
                   SubIntake::GetInstance().IntakeRight();}
        );
    }

    frc2::CommandPtr StopIntake() {
        return RunOnce (
            [] {SubIntake::GetInstance().Stop();}
        );
    }

 frc2::CommandPtr Outtake(){ 
     return StartEnd(
            [] {SubIntake::GetInstance().DeployIntake();
               SubIntake::GetInstance().OuttakeLeft();
               SubIntake::GetInstance().OuttakeRight();},
            [] {SubIntake::GetInstance().Stop();
                SubIntake::GetInstance().RetractIntake();}    
     );
    }

    frc2::CommandPtr StartOuttake() {
        return RunOnce (
            [] {SubIntake::GetInstance().OuttakeLeft();
                   SubIntake::GetInstance().OuttakeRight();}
        );
    }

    frc2::CommandPtr StopOuttake() {
        return RunOnce (
            [] {SubIntake::GetInstance().Stop();}
        );
    }

    frc2::CommandPtr ClawClose(){
       return Either(RunOnce([]{SubClaw::GetInstance().ClawClampedCone();}), 
                    RunOnce([]{SubClaw::GetInstance().ClawClampedCube();}),
                    []{return RobotContainer::isConeMode;});
    }

        frc2::CommandPtr ClawOpen(){
        return RunOnce(
        [] {
            SubClaw::GetInstance().ClawUnclamped();
        }
        );
    }

}