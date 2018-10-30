#ifndef __SERVO_HW__
#define __SERVO_HW__

#include <pigpiod_if2.h>
#include <stdint.h>

/* which GPIOi pin (on the standard rPi header) is being used for servo pulses */
extern int32_t PIN_SIGNAL;

int32_t init_hw     (int32_t* pihnd);
int32_t update_hw   (int32_t* pihnd, double position);
int32_t finalize_hw (int32_t* pihnd);

#endif
