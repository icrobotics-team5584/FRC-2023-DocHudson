// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdGridCommands.h"
#include "commands/DriveCommands.h"
#include "commands/GamePieceCommands.h"

/*grid layout low -->  11 12 13     21 22 23     31 32 33
              mid -->  14 15 16     24 25 26     34 35 36
              hig -->  17 18 19     27 28 29     37 38 39
          ------------------------------------------------------------
                    DStation1       DStation2       DStation3
*/

namespace cmd {
    using namespace frc2::cmd;

    frc2::CommandPtr Score11() {
       return Sequence( 
       Drive11(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }

    frc2::CommandPtr Score12() {
       return Sequence(
       Drive12(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }

frc2::CommandPtr Score13() {
       return Sequence(
       Drive13(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }

frc2::CommandPtr Score14() {
       return Sequence(
       Drive14(),
       // armmid(),
       ClawReleaseCone()
       //StowArm();
       );
    }

frc2::CommandPtr Score15() {
       return Sequence(
       Drive15(),
       // armmid(),
       ClawReleaseCube()
       //StowArm();
       );
    }

frc2::CommandPtr Score16() {
       return Sequence(
       Drive16(),
       // armmid(),
       ClawReleaseCone()
       //StowArm();
       );
    }

frc2::CommandPtr Score17() {
       return Sequence(
       Drive17(),
       // armhigh(),
       ClawReleaseCone()
       //StowArm();
       );
    }

frc2::CommandPtr Score18() {
       return Sequence(
       Drive18(),
       // armhigh(),
       ClawReleaseCube()
       //StowArm();
       );
    }

frc2::CommandPtr Score19() {
       return Sequence(
       Drive19(),
       // armhigh(),
       ClawReleaseCone()
       //StowArm();
       );
    }

frc2::CommandPtr Score21() {
       return Sequence(
       Drive21(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score22() {
       return Sequence(
       Drive22(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score23() {
       return Sequence(
       Drive23(),
       // armlow(),
       ClawReleaseCone()
      //StowArm();
       );
    }
frc2::CommandPtr Score24() {
       return Sequence(
       Drive24(),
       // armmid(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score25() {
       return Sequence(
       Drive25(),
       // armmid(),
       ClawReleaseCube()
       //StowArm();
       );
    }
frc2::CommandPtr Score26() {
       return Sequence(
       Drive26(),
       // armmid(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score27() {
       return Sequence(
       Drive27(),
       // armhigh(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score28() {
       return Sequence(
       Drive28(),
       // armhigh(),
       ClawReleaseCube()
       //StowArm();
       );
    }
frc2::CommandPtr Score29() {
       return Sequence(
       Drive29(),
       // armhigh(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score31() {
       return Sequence(
       Drive31(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score32() {
       return Sequence(
       Drive32(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score33() {
       return Sequence(
       Drive33(),
       // armlow(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score34() {
       return Sequence(
       Drive34(),
       // armmid(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score35() {
       return Sequence(
       Drive35(),
       // armmid(),
       ClawReleaseCube()
       //StowArm();
       );
    }
frc2::CommandPtr Score36() {
       return Sequence(
       Drive36(),
       // armmid(),
       ClawReleaseCone()
       //StowArm();
       );
    }
frc2::CommandPtr Score37() {
       return Sequence(
       Drive37(),
       // armhigh(),
       ClawReleaseCone()
       //StowArm();
       );
    }  
frc2::CommandPtr Score38() {
       return Sequence(
       Drive38(),
       // armhigh(),
       ClawReleaseCube()
       //StowArm();
       );
    }
frc2::CommandPtr Score39() {
       return Sequence(
       Drive39(),
       // armhigh(),
       ClawReleaseCone()
       //StowArm();
       );
    }
}