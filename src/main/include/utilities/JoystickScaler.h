// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once
#include <frc/XboxController.h>
#include <iostream>

class JoystickScaler :
public frc::XboxController{
 public:
   enum Hand {
      left, 
      right
  }; 
  JoystickScaler(int deviceID, double scaleLeft, double scaleRight);
  double GetScaledX(Hand hand);
  double GetScaledY(Hand hand);
  void SetLeftScale(double scale);
  void SetRightScale(double scale);

 private:
 double _scaleLeft;
 double _scaleRight;
 double _scale;
};
