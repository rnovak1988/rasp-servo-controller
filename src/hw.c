#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <pigpiod_if2.h>
#include <stdio.h>
#include "hw.h"

int32_t PIN_SIGNAL = -1;

int32_t init_hw(int32_t* pi) {
  
  if (pi == NULL || *pi >= 0) return EINVAL;
  
  int32_t status = pigpio_start(NULL, NULL);

  if (status < 0) return status;

  /* if status is >= 0, then it is interpreted as a handle */
  *pi = status;

  /* set the pulse width to 50% (or center position) by default */
  status = set_servo_pulsewidth(*pi, PIN_SIGNAL, 1500);

  return status;
}

/* position is a percentage (from zero to 1) of the position
 *  of the servo armature
 */
int32_t update_hw (int32_t* pi, double position) {

  if (pi == NULL) return EINVAL;
  if (position < 0.0 || position > 1.0) return EINVAL;

  return set_servo_pulsewidth(*pi, PIN_SIGNAL,((int32_t)(500.0 + (2000.0 * position))));
}


/*
 * disable all servo pulses on the GPIO pin, and disconnect from
 * the pigpio daemon
 */
int32_t finalize_hw (int32_t* pi) {
  int32_t status = set_servo_pulsewidth(*pi, PIN_SIGNAL, 0);
  pigpio_stop(*pi);
  *pi = -1;
  return status;
}

