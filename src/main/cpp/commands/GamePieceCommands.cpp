#include "commands/GamePieceCommands.h"
#include "subsystems/SubClaw.h"
#include "subsystems/SubIntake.h"

namespace cmd {
    using namespace frc2::cmd;

   

    frc2::CommandPtr Intake(){
        return StartEnd(
            [] {SubIntake::GetInstance().IntakeLeft();
                SubIntake::GetInstance().IntakeRight();},
            [] {SubIntake::GetInstance().Stop();}    
        );
    }

 frc2::CommandPtr Outtake(){
        return StartEnd(
            [] {SubIntake::GetInstance().OuttakeLeft();
                SubIntake::GetInstance().OuttakeRight();},
            [] {SubIntake::GetInstance().Stop();}    
        );
    }




    frc2::CommandPtr ClawClose(){
        return RunOnce(
        [] {
            SubClaw::GetInstance().ClawClamped();
        }
        );
    }

        frc2::CommandPtr ClawOpen(){
        return RunOnce(
        [] {
            SubClaw::GetInstance().ClawUnclamped();
        }
        );
    }

}