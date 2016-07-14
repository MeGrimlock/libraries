/*
 * Copyright (C) 2015-2016  Intel Corporation. All rights reserved.
 *
 * This file is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <assert.h>

#include <AP_Math/AP_Math.h>

#include "SIM_Calibration.h"

#define MAX_ANGULAR_SPEED (2 * M_PI)

#include <stdio.h>

SITL::Calibration::Calibration(const char *home_str, const char *frame_str)
    : Aircraft(home_str, frame_str)
{
    mass = 1.5f;
}

void SITL::Calibration::update(const struct sitl_input& input)
{
    Vector3f rot_accel{0, 0, 0};

    float switcher_pwm = input.servos[4];
    if (switcher_pwm < 1100) {
        _stop_control(input, rot_accel);
    } else if (switcher_pwm < 1200) {
        _attitude_control(input, rot_accel);
    } else {
        _angular_velocity_control(input, rot_accel);
    }

    accel_body(0, 0, 0);
    update_dynamics(rot_accel);
    update_position();

    // update magnetic field
    update_mag_field_bf();
}

void SITL::Calibration::_stop_control(const struct sitl_input& input,
                                      Vector3f& rot_accel)
{
    Vector3f desired_angvel{0, 0, 0};
    Vector3f error =  desired_angvel - gyro;
    float dt = frame_time_us * 1.0e-6f;
    rot_accel = error * (1.0f / dt);
    /* Provide a somewhat "smooth" transition */
    rot_accel *= 0.002f;
}

void SITL::Calibration::_attitude_control(const struct sitl_input& input,
                                          Vector3f& rot_accel)
{
    float desired_roll = -M_PI + 2 * M_PI * (input.servos[5] - 1000) / 1000.f;
    float desired_pitch = -M_PI + 2 * M_PI * (input.servos[6] - 1000) / 1000.f;
    float desired_yaw = -M_PI + 2 * M_PI * (input.servos[7] - 1000) / 1000.f;
    float dt = frame_time_us * 1.0e-6f;

    Quaternion desired_q;
    desired_q.from_euler(desired_roll, desired_pitch, desired_yaw);
    desired_q.normalize();

    Quaternion current_q;
    current_q.from_rotation_matrix(dcm);
    current_q.normalize();

    Quaternion error_q = desired_q / current_q;

    Vector3f angle_differential;
    error_q.normalize();
    error_q.to_axis_angle(angle_differential);

    Vector3f desired_angvel = angle_differential * (1 / dt);
    /* Provide a somewhat "smooth" transition */
    desired_angvel *= .005f;

    Vector3f error = desired_angvel - gyro;
    rot_accel = error * (1.0f / dt);
}

void SITL::Calibration::_angular_velocity_control(const struct sitl_input& in,
                                                  Vector3f& rot_accel)
{
    Vector3f axis{(float)(in.servos[5] - 1500),
                  (float)(in.servos[6] - 1500),
                  (float)(in.servos[7] - 1500)};
    float theta = MAX_ANGULAR_SPEED * (in.servos[4] - 1200) / 800.f;
    float dt = frame_time_us * 1.0e-6f;

    axis.normalize();

    Vector3f desired_angvel = axis * theta;
    Vector3f error = desired_angvel - gyro;

    rot_accel = error * (1.0f / dt);
    /* Provide a somewhat "smooth" transition */
    rot_accel *= .05f;
}
