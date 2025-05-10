#ifndef MACHINE_ROOM_H_
#define MACHINE_ROOM_H_

#include "constants/ConfigurationFields.h"
#include "constants/MotorSettings.h"
#include "constants/PinList.h"
#include "models/Motor.h"
#include <stdint.h>

#define PHYSYCAL_CONTROLLER 1

struct settings {
  uint8_t speed; //!< From 1 - 255, default 255
};

typedef struct settings settings_t;

void machine_room_init(void);
void machine_room_reset(void);
void machine_room_update(int module_y, int speed, int x);

#endif /* MACHINE_ROOM_H_ */
