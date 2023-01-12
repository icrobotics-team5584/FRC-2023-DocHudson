#include "commands/GamePieceCommands.h"
#include "subsystems/SubClaw.h"
#include "subsystems/SubIntake.h"

namespace cmd {
    using namespace frc2::cmd;




    frc2::CommandPtr ClawExpand() {
        return RunOnce(
            [] {SubClaw::GetInstance().BothExtended();}
        );
    }

    frc2::CommandPtr ClawGrabCone(){
        return RunOnce(
         [] {SubClaw::GetInstance().BothRetracted();}   
        );
    }

    frc2::CommandPtr ClawGrabCube(){
        return RunOnce(
        [] {
            SubClaw::GetInstance().OneExtended();
            SubClaw::GetInstance().OneRetracted();
        }
        );
    }

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

}