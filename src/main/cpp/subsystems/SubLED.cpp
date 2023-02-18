// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/SubLED.h"
#include <frc/AddressableLED.h>
#include "commands/ArmCommands.h"
#include "RobotContainer.h"

SubLED::SubLED() {
  m_led.SetLength(kLength);
  m_led.SetData(m_ledBuffer);
  m_led.Start();
}
// This method will be called once per scheduler run
void SubLED::Periodic() {
    Colour();
}

void SubLED::Colour() {
  if (RobotContainer::isConeMode == false) {
    for (int i = 0; i < kLength; i++) {
      m_ledBuffer[i].SetRGB(213, 17, 247);
    }
  } else if (RobotContainer::isConeMode == true) {
    for (int i = 0; i < kLength; i++) {
      m_ledBuffer[i].SetRGB(247, 121, 17);
    }
  }

  m_led.SetData(m_ledBuffer);
}
