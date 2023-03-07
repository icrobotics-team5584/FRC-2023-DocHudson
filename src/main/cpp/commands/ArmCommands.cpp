#include "commands/ArmCommands.h"
#include "subsystems/SubArm.h"
#include "subsystems/SubIntake.h"
#include "subsystems/SubDrivebase.h"
#include "units/length.h"
#include "RobotContainer.h"
#include <frc/DriverStation.h>

namespace cmd{
    using namespace frc2::cmd;

    frc2::CommandPtr ArmToSafePosition() {
      return Either(
          ArmToPos(50_cm, 110_cm).Until([] {
            return SubArm::GetInstance().GetEndEffectorPosition().Y() > 70_cm;
          }),
          None(), [] {
            return SubArm::GetInstance().GetEndEffectorPosition().Y() < 70_cm;
          });
    }

    frc2::CommandPtr ArmToHighCone(){return ArmToSafePosition().AndThen(ArmToPos(122_cm, 125_cm));} 
    frc2::CommandPtr ArmToMidCone(){return  ArmToSafePosition().AndThen(ArmToPos(95_cm,90_cm));} //gtg

    frc2::CommandPtr ArmToHighCube(){return  ArmToSafePosition().AndThen(ArmToPos(122_cm, 110_cm));} 
    frc2::CommandPtr ArmToMidCube(){return  ArmToSafePosition().AndThen(ArmToPos(70_cm, 75_cm));}

    frc2::CommandPtr ArmToLowCubeOrCone() {return ArmToPos(45_cm, 15_cm);}
    frc2::CommandPtr ArmToLoadingStation(){return ArmToPos(0.498_m, 0.781_m);}
	frc2::CommandPtr ArmToDefaultLocation(){return ArmToPos(44_cm, 0_cm);} //gtg

    frc2::CommandPtr ArmPickUp(){
        return RunOnce([]() { SubArm::GetInstance().DriveTo(0.195_tr, -0.43_tr); })
            .AndThen(WaitUntil(
                []() { return SubArm::GetInstance().CheckPosition(); }));
    } 

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

    frc2::CommandPtr ArmToPos(auto x, auto y) {
        return RunOnce([x, y]() { SubArm::GetInstance().ArmPos(x, y); })
            .AndThen(WaitUntil(
                []() { return SubArm::GetInstance().CheckPosition(); }));
    }

     frc2::CommandPtr ArmToScoringHeight(grids::Height height) {
        switch (height) {
            case grids::Height::High:
                return ArmToHigh();
            case grids::Height::Middle:
                return ArmToMid();
            case grids::Height::Low:
                return ArmToLowCubeOrCone();
            case grids::Height::LS:
                return ArmToLoadingStation();
            default:
                return None();
        };
    }

    frc2::CommandPtr ManualArmMove(double xSpeed, double ySpeed) {
        return Run([xSpeed, ySpeed]{
            auto eePos = SubArm::GetInstance().GetEndEffectorTarget();
            eePos = eePos + frc::Translation2d(xSpeed*1_mm, ySpeed*1_mm);
            SubArm::GetInstance().ArmPos(eePos.X(), eePos.Y());
        });
    }

    frc2::CommandPtr CoastModeOverride() {
        return StartEnd(
          [] {
            SubDriveBase::GetInstance().SetNeutralMode(NeutralMode::Coast);
            SubArm::GetInstance().SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
          },
          [] {
            SubDriveBase::GetInstance().SetNeutralMode(NeutralMode::Brake);
            SubArm::GetInstance().SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
          }).IgnoringDisable(true).Until([]{return frc::DriverStation::IsEnabled();});
    }

    frc2::CommandPtr DriveBottomArmToSwitch() {
        return StartEnd([] { SubArm::GetInstance().DriveBottomAt(0.3); },
                        [] { SubArm::GetInstance().DriveBottomAt(0); })
            .Until([] { return SubArm::GetInstance().LocatingSwitchIsHit(); });
    }
}