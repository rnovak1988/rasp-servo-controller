#ifndef __SERVO_HW__
#define __SERVO_HW__

#include <pigpiod_if2.h>
#include <stdint.h>

/* which GPIOi pin (on the standard rPi header) is being used for servo pulses */
extern int32_t PIN_SIGNAL;

/*
 * if the value of this global is TRUE, then the servo position is inverted
 * in relation to the position bar
 */
extern int32_t INVERT;

int32_t init_hw     (int32_t* pihnd);
int32_t update_hw   (int32_t* pihnd, double position);
int32_t finalize_hw (int32_t* pihnd);

#endif
