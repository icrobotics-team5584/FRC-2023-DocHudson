#pragma once
#include <frc2/command/commands.h>

namespace cmd {
    frc2::CommandPtr PPDrivePath(std::string pathName);

    frc2::CommandPtr ScorePos(frc2::CommandPtr&& scoreCommand);
}