// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "commands/CmdGridCommands.h"
#include "commands/DriveCommands.h"
#include "commands/GamePieceCommands.h"
#include "commands/ArmCommands.h"
#include <frc/geometry/Translation2d.h>


/*

grid layout 


drive number blue             01 02 03     04 05 06     07 08 09

                     low -->  11 12 13     21 22 23     31 32 33
                     mid -->  14 15 16     24 25 26     34 35 36
                     hig -->  17 18 19     27 28 29     37 38 39
          ------------------------------------------------------------
                    DStation1       DStation2       DStation3
*/

namespace cmd {
    using namespace frc2::cmd;


    frc2::CommandPtr Score11() {
       return Sequence( 
       Drive01(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

    frc2::CommandPtr Score12() {
       return Sequence(
       Drive02(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score13() {
       return Sequence(
       Drive03(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score14() {
       return Sequence(
       Drive01(),
       ArmToMidCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score15() {
       return Sequence(
       Drive02(),
       ArmToMidCube(),
       ClawReleaseCube(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score16() {
       return Sequence(
       Drive03(),
       ArmToMidCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score17() {
       return Sequence(
       Drive01(),
       ArmToHighCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score18() {
       return Sequence(
       Drive02(),
       ArmToHighCube(),
       ClawReleaseCube(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score19() {
       return Sequence(
       Drive03(),
       ArmToHighCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }

frc2::CommandPtr Score21() {
       return Sequence(
       Drive04(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score22() {
       return Sequence(
       Drive05(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score23() {
       return Sequence(
       Drive06(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score24() {
       return Sequence(
       Drive04(),
       ArmToMidCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score25() {
       return Sequence(
       Drive05(),
       ArmToMidCube(),
       ClawReleaseCube(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score26() {
       return Sequence(
       Drive06(),
       ArmToMidCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score27() {
       return Sequence(
       Drive04(),
       ArmToHighCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score28() {
       return Sequence(
       Drive05(),
       ArmToHighCube(),
       ClawReleaseCube(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score29() {
       return Sequence(
       Drive06(),
       ArmToHighCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score31() {
       return Sequence(
       Drive07(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score32() {
       return Sequence(
       Drive08(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score33() {
       return Sequence(
       Drive09(),
       ArmToLowCubeOrCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score34() {
       return Sequence(
       Drive07(),
       ArmToMidCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score35() {
       return Sequence(
       Drive08(),
       ArmToMidCube(),
       ClawReleaseCube(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score36() {
       return Sequence(
       Drive09(),
       ArmToMidCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score37() {
       return Sequence(
       Drive07(),
       ArmToHighCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }  
frc2::CommandPtr Score38() {
       return Sequence(
       Drive08(),
       ArmToHighCube(),
       ClawReleaseCube(),
       ArmToDefaultLocation()
       );
    }
frc2::CommandPtr Score39() {
       return Sequence(
       Drive09(),
       ArmToHighCone(),
       ClawReleaseCone(),
       ArmToDefaultLocation()
       );
    }
}