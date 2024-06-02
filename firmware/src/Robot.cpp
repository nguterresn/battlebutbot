#include "Robot.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "MachineRoom.h"

extern settings_t robot_settings;

static void robot_update(settings_t* settings);
static void robot_load_configuration(void);

/**
 * @brief Construct a new Robot:: Robot object
 *
 */
bool robot_init(void)
{
  if (!EEPROM.begin(EEPROM_SIZE)) {
    return false;
  }

  // Machine room should be called first.
  machine_room_init();
  // Load the configuration as soon as the robot boots.
  robot_load_configuration();

  return true;
}

static void robot_update(settings_t* settings)
{
  memcpy(&robot_settings, settings, sizeof(settings_t));
}

/**
 * @brief Save new configuration on the EEPROM
 *
 * @param configuration as an integer
 * @param speed as an integer
 */
void robot_save_configuration(int speed)
{
  // Confirm all of them are the same and return.
  if (robot_settings.speed == speed) {
    return;
  }

  speed &= UINT8_MAX;

  // Save on EEPROM
  EEPROM.put(EEPROM_SPEED_INDEX, speed);
  EEPROM.commit();

  settings_t saved_settings = { .speed = (uint8_t)speed };

  // Save on RAM
  robot_update(&saved_settings);
}

/**
 * @brief Load configuration from EEPROM
 */
static void robot_load_configuration(void)
{
  uint8_t speed            = EEPROM.read(EEPROM_SPEED_INDEX);
  settings_t load_settings = {
    .speed = speed ? (uint8_t)MOTOR_SPEED_DEFAULT : speed
  };

  robot_update(&load_settings);
}

/**
 * @brief Method feedback when a client connects to the webpage
 */
void robot_connect(void)
{
  machine_room_reset();
}

/**
 * @brief Serializes the configuration, speed and mode into hex
 *
 * @param buffer of 10 bytes (set on `WebServer.cpp`)
 * @return int
 */
int robot_serialize_for_request(char* buffer)
{
  return sprintf(buffer, "%02x", robot_settings.speed);
}
