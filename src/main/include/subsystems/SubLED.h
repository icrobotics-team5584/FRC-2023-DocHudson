// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/AddressableLED.h>
#include <array>
#include <constants.h>

class SubLED : public frc2::SubsystemBase {
 public:
  static bool autoDriving;

  SubLED();

  static SubLED& GetInstance() {
    static SubLED inst;
    return inst;
  }

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  void SetColour();

 private:
  static constexpr int kLength = 31;

  frc::AddressableLED m_led{pwm::LEDs};
  std::array<frc::AddressableLED::LEDData, kLength> m_ledBuffer;

  int firstPixelHue = 0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
