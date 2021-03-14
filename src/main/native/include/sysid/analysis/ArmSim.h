// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <Eigen/Core>
#include <units/time.h>
#include <units/voltage.h>

namespace sysid {

class ArmSim {
 public:
  /**
   * @param Ks              Static friction gain.
   * @param Kv              Velocity gain.
   * @param Ka              Acceleration gain.
   * @param Kcos            Gravity cosine gain.
   * @param initialPosition Initial elevator position.
   * @param initialVelocity Initial elevator velocity.
   */
  ArmSim(double Ks, double Kv, double Ka, double Kcos,
         double initialPosition = 0.0, double initialVelocity = 0.0);

  /**
   * Simulates affine state-space system dx/dt = Ax + Bu + c sgn(x) + d forward
   * dt seconds.
   *
   * @param voltage Voltage to apply over the timestep.
   * @param dt      Sammple period.
   */
  void Update(units::volt_t voltage, units::second_t dt);

  /**
   * Returns the position.
   */
  double GetPosition() const;

  /**
   * Returns the velocity.
   */
  double GetVelocity() const;

  /**
   * Returns the acceleration for the current state and given input.
   */
  double GetAcceleration(units::volt_t voltage) const;

  /**
   * Resets model position and velocity.
   */
  void Reset(double position = 0.0, double velocity = 0.0);

 private:
  Eigen::Matrix<double, 1, 1> m_A;
  Eigen::Matrix<double, 1, 1> m_B;
  Eigen::Matrix<double, 1, 1> m_c;
  Eigen::Matrix<double, 1, 1> m_d;
  Eigen::Matrix<double, 2, 1> m_x;
};

}  // namespace sysid
