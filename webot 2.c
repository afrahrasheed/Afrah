#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/light_sensor.h>
#include <webots/gps.h>
#include <webots/led.h>

// Simulation constants
#define TIME_STEP 64       // Simulation time step in milliseconds
#define MAX_SPEED 6.28     // Maximum motor speed
#define LIGHT_THRESHOLD 500.0
#define WALL_THRESHOLD 100.0
#define GPS_TOLERANCE 0.01 // Tolerance for GPS coordinate comparison

// Function to detect if the robot is in a dead-end
bool detect_dead_end();

int main(int argc, char **argv) {
  // Initialize the Webots API
  wb_robot_init();

  // Configure motors
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);

  double left_speed = MAX_SPEED;
  double right_speed = MAX_SPEED;

  // Arrays to store dead-end data
  double light_readings[10];
  double gps_deadends[10][3];
  int dead_end_count = 0, brightest_deadend_index = 0;
  double max_light_intensity = 0;

  // Configure distance sensors
  WbDeviceTag distance_sensors[8];
  char sensor_name[8];
  for (int i = 0; i < 8; i++) {
    sprintf(sensor_name, "ps%d", i);
    distance_sensors[i] = wb_robot_get_device(sensor_name);
    wb_distance_sensor_enable(distance_sensors[i], TIME_STEP);
  }

  // Configure light sensor
  WbDeviceTag light_sensor = wb_robot_get_device("ls0");
  wb_light_sensor_enable(light_sensor, TIME_STEP);

  // Configure GPS sensor
  WbDeviceTag gps = wb_robot_get_device("gps");
  wb_gps_enable(gps, TIME_STEP);

  // Main simulation loop
  while (wb_robot_step(TIME_STEP) != -1) {
    const double *current_gps = wb_gps_get_values(gps);

    // Read distance sensor values
    bool front_wall = wb_distance_sensor_get_value(distance_sensors[7]) > WALL_THRESHOLD;
    bool left_wall = wb_distance_sensor_get_value(distance_sensors[5]) > WALL_THRESHOLD;
    bool left_corner = wb_distance_sensor_get_value(distance_sensors[6]) > WALL_THRESHOLD;

    // Read light sensor value
    double light_value = wb_light_sensor_get_value(light_sensor);

    // Handle dead-end detection
    if (detect_dead_end()) {
      if (dead_end_count < 10) {
        // Store data for the dead-end
        light_readings[dead_end_count] = light_value;
        gps_deadends[dead_end_count][0] = current_gps[0];
        gps_deadends[dead_end_count][1] = current_gps[1];
        gps_deadends[dead_end_count][2] = current_gps[2];
        dead_end_count++;
        printf("Dead-end %d detected with light intensity %f at coordinates x = %f, y = %f, z = %f\n", 
                dead_end_count, light_value, current_gps[0], current_gps[1], current_gps[2]);
      }

      // Once 10 dead-ends are recorded, find the brightest
      if (dead_end_count == 10) {
        for (int i = 0; i < 10; i++) {
          if (light_readings[i] > max_light_intensity) {
            max_light_intensity = light_readings[i];
            brightest_deadend_index = i;
          }
        }
        printf("Brightest dead-end: #%d with light intensity %f at x = %f, y = %f, z = %f\n",
               brightest_deadend_index + 1, max_light_intensity,
               gps_deadends[brightest_deadend_index][0],
               gps_deadends[brightest_deadend_index][1],
               gps_deadends[brightest_deadend_index][2]);
        dead_end_count++;
      }

      // Check if the robot has reached the brightest dead-end
      if (fabs(current_gps[0] - gps_deadends[brightest_deadend_index][0]) < GPS_TOLERANCE &&
          fabs(current_gps[1] - gps_deadends[brightest_deadend_index][1]) < GPS_TOLERANCE &&
          fabs(current_gps[2] - gps_deadends[brightest_deadend_index][2]) < GPS_TOLERANCE) {
        printf("\n\nReached the brightest dead-end!\n\n");

        // Turn on LEDs
        for (int i = 0; i <= 6; i++) {
          char led_name[8];
          sprintf(led_name, "led%d", i);
          WbDeviceTag led = wb_robot_get_device(led_name);
          wb_led_set(led, 1); // Turn LED on
        }
        break;
      }
    }
