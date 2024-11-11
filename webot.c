#include <webots/robot.h>
#include <webots/light_sensor.h>
#include <webots/motor.h>
#include <stdio.h>

#define TIME_STEP 64  // Time step for simulation in ms
#define MAX_SPEED 6.28
#define NUM_LIGHT_SENSORS 8

int main(int argc, char **argv) {
  // Initialize the Webots API
  wb_robot_init();
  
  // Get motor devices
  WbDeviceTag left_motor = wb_robot_get_device("left wheel motor");
  WbDeviceTag right_motor = wb_robot_get_device("right wheel motor");
  
  // Set motors to velocity control mode
  wb_motor_set_position(left_motor, INFINITY);
  wb_motor_set_position(right_motor, INFINITY);
  
  // Initialize light sensors
  WbDeviceTag light_sensors[NUM_LIGHT_SENSORS];
  char light_sensor_name[50];
  
  for (int ind = 0; ind < NUM_LIGHT_SENSORS; ++ind) {
    sprintf(light_sensor_name, "ls%d", ind); // Assuming sensors are named ls0 to ls7
    light_sensors[ind] = wb_robot_get_device(light_sensor_name);
    wb_light_sensor_enable(light_sensors[ind], TIME_STEP);
  }

  // Main loop
  while (wb_robot_step(TIME_STEP) != -1) {
    double light_values[NUM_LIGHT_SENSORS];
    double left_speed = MAX_SPEED;
    double right_speed = MAX_SPEED;

    // Read all light sensor values
    for (int ind = 0; ind < NUM_LIGHT_SENSORS; ++ind) {
      light_values[ind] = wb_light_sensor_get_value(light_sensors[ind]);
    }

    // Determine which side has more light
    double left_light_sum = light_values[0] + light_values[1]; // Left sensors
    double right_light_sum = light_values[2] + light_values[3]; // Right sensors

    if (left_light_sum > right_light_sum) {
      // More light on the left, turn right
      left_speed = MAX_SPEED;
      right_speed = MAX_SPEED / 2;
    } else if (right_light_sum > left_light_sum) {
      // More light on the right, turn left
      left_speed = MAX_SPEED / 2;
      right_speed = MAX_SPEED;
    }

    // Set motor velocities based on sensor readings
    wb_motor_set_velocity(left_motor, left_speed);
    wb_motor_set_velocity(right_motor, right_speed);

    // Display light sensor values for debugging
    printf("Light Sensor Values: ");
    for (int ind = 0; ind < NUM_LIGHT_SENSORS; ++ind) {
      printf("%f ", light_values[ind]);
    }
    printf("\n");
  }

  // Cleanup the Webots API
  wb_robot_cleanup();

  return 0;
}