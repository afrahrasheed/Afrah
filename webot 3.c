#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <webots/gps.h>
#include <webots/led.h>

#define TIME_STEP 64       // Time step for the simulation (ms)
#define MAX_SPEED 6.28     // Maximum motor speed
#define WALL_THRESHOLD 100.0  // Threshold to detect walls
#define GPS_TOLERANCE 0.01    // GPS coordinate tolerance for comparisons

// Dead-end detection
bool detect_dead_end(WbDeviceTag *distance_sensors, int *dead_end_count, double *dead_end_timer);

int main() {
  // Initialize the Webots API
  wb_robot_init();

  // Enable motors
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);

  // Sensor initialization
  WbDeviceTag distance_sensors[8];
  WbDeviceTag light_sensor = wb_robot_get_device("ls0");
  WbDeviceTag gps_sensor = wb_robot_get_device("gps");

  // Enable sensors
  for (int i = 0; i < 8; i++) {
    char sensor_name[8];
    sprintf(sensor_name, "ps%d", i);
    distance_sensors[i] = wb_robot_get_device(sensor_name);
    wb_distance_sensor_enable(distance_sensors[i], TIME_STEP);
  }
  wb_light_sensor_enable(light_sensor, TIME_STEP);
  wb_gps_enable(gps_sensor, TIME_STEP);

  // Initialize variables
  double left_speed = MAX_SPEED;
  double right_speed = MAX_SPEED;
  double light_values[10] = {0};
  double dead_end_coordinates[10][3] = {0};
  int dead_end_index = 0;
  int brightest_index = -1;
  double brightest_light = 0.0;
  int dead_end_count = 0;
  double dead_end_timer = 0.0;

  // Main simulation loop
  while (wb_robot_step(TIME_STEP) != -1) {
    // Get sensor readings
    const double *gps_values = wb_gps_get_values(gps_sensor);
    double front_distance = wb_distance_sensor_get_value(distance_sensors[7]);
    double left_distance = wb_distance_sensor_get_value(distance_sensors[5]);
    double light_value = wb_light_sensor_get_value(light_sensor);

    // Dead-end detection
    if (detect_dead_end(distance_sensors, &dead_end_count, &dead_end_timer)) {
      if (dead_end_index < 10) {
        // Record light value and GPS coordinates
        light_values[dead_end_index] = light_value;
        dead_end_coordinates[dead_end_index][0] = gps_values[0];
        dead_end_coordinates[dead_end_index][1] = gps_values[1];
        dead_end_coordinates[dead_end_index][2] = gps_values[2];
        printf("Dead-end %d detected at coordinates: x=%f, y=%f, z=%f\n",
               dead_end_index + 1, gps_values[0], gps_values[1], gps_values[2]);

        // Update the brightest dead-end
        if (light_value > brightest_light) {
          brightest_light = light_value;
          brightest_index = dead_end_index;
        }
        dead_end_index++;
      }
    }

    // Check if the robot has reached the brightest dead-end
    if (brightest_index >= 0 &&
        fabs(gps_values[0] - dead_end_coordinates[brightest_index][0]) < GPS_TOLERANCE &&
        fabs(gps_values[1] - dead_end_coordinates[brightest_index][1]) < GPS_TOLERANCE &&
        fabs(gps_values[2] - dead_end_coordinates[brightest_index][2]) < GPS_TOLERANCE) {
      printf("Reached brightest dead-end: Light=%f at x=%f, y=%f, z=%f\n",
             brightest_light, dead_end_coordinates[brightest_index][0],
             dead_end_coordinates[brightest_index][1],
             dead_end_coordinates[brightest_index][2]);

      // Turn on LEDs
      for (int i = 0; i < 7; i++) {
        char led_name[8];
        sprintf(led_name, "led%d", i);
        WbDeviceTag led = wb_robot_get_device(led_name);
        wb_led_set(led, 1);
      }
      break;
    }

    // Wall-following behavior
    if (front_distance > WALL_THRESHOLD) {
      // Turn right if a wall is ahead
      left_speed = MAX_SPEED;
      right_speed = -MAX_SPEED;
    } else if (left_distance > WALL_THRESHOLD) {
      // Move forward if a wall is on the left
      left_speed = MAX_SPEED / 2;
      right_speed = MAX_SPEED / 2;
    } else {
      // Turn left if no wall is on the left
      left_speed = MAX_SPEED / 4;
      right_speed = MAX_SPEED;
    }

    // Set motor speeds
    wb_motor_set_velocity(left_motor, left_speed);
    wb_motor_set_velocity(right_motor, right_speed);
  }

  // Cleanup
  wb_robot_cleanup();
  return 0;
}

bool detect_dead_end(WbDeviceTag *distance_sensors, int *dead_end_count, double *dead_end_timer) {
  double front_distance = wb_distance_sensor_get_value(distance_sensors[7]);
  double current_time = wb_robot_get_time();

  if (front_distance > WALL_THRESHOLD) {
    if (*dead_end_count == 0 || (current_time - *dead_end_timer) > 1.7) {
      *dead_end_timer = current_time;
      (*dead_end_count)++;
    }
  }

  if (*dead_end_count >= 2) {
    *dead_end_count = 0;
    return true;
  }

  if ((current_time - *dead_end_timer) > 10.0) {
    *dead_end_count = 0;
  }

  return false;
}
