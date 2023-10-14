#ifndef ROBOT_H_
#define ROBOT_H_

#include <Arduino.h>
#include "MachineRoom.h"

#ifdef __cplusplus
extern "C" {
#endif

void robot_init(void);
void robot_update(int configuration, int speed);
void robot_connect(void);
void robot_save_configuration(int configuration, int speed);
void robot_load_configuration(void);
void robot_flip(void);
int robot_get_battery(void);
int robot_serialize_for_request(char* buffer);

#ifdef __cplusplus
}
#endif

#endif /* ROBOT_H_ */
