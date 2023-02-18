// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/Commands.h>
#include "utilities/Grids.h"

namespace cmd {
  frc2::CommandPtr Score(grids::Column column, grids::Height height);
};