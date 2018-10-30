#include "servo_controller.h"

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>

/* ncurses installs its own interrupt handler for keyboard events, so we capture those too */
static void (*previous_handler)(int32_t) = NULL;

/* global variable that allows for shutting down the gpio connection during interrupt */
static int32_t         pihandle  = -1;

/* sentinal variable to indicate whether runtime should continue */
static int32_t         running   = 1;
static pthread_mutex_t m_running = PTHREAD_MUTEX_INITIALIZER;


/*
 * send a signal to the running program by (atomically) changing
 * the value of running to 0. 
 * the gpio connection is stopped, and a previous interrupt handler
 * (if it exists) is both re-installed and called if it is not one of
 * "IGNORE" or "DEFAULT"
 */
void interrupt_handler (int32_t signum) {
  if (pthread_mutex_lock(&m_running) == EXIT_SUCCESS) {
    running = 0;
    pthread_mutex_unlock(&m_running);
  }

  finalize_hw(&pihandle);

  if (previous_handler != NULL) {
    signal(SIGINT, previous_handler);
    if (previous_handler != SIG_DFL && previous_handler != SIG_IGN) {
      previous_handler(signum);
    }
  }

}

/*
 * Basic program which allows the control of a servo, as sort of a 
 * joystick input. Arrow keys <- and -> move the servo in the appropriate
 * direction. 
 * future versions will include ability to configure/flip direction
 */
int32_t main (int32_t argc, char* argv[]) {
  int32_t status = EXIT_SUCCESS;
  struct _ui_ ui; 

  PIN_SIGNAL = 12;

  status = init_ui(&ui);
  status = init_hw(&pihandle);

  if (status != EXIT_SUCCESS) {
    fprintf(stderr, "%s\n", status < 0 ? pigpio_error(status) : strerror(status));
  }

  previous_handler = signal(SIGINT, interrupt_handler);

  int32_t keyed, _running = running;
  while (_running) {

    keyed = wgetch(ui.position_bar);

    switch (keyed) {
      case KEY_LEFT:
        update_ui(&ui,- 1);
      break;
      case KEY_RIGHT:
        update_ui(&ui, 1);
      break;
      default:
      break;
    }

    status = update_hw(&pihandle, CURSOR_PERCENTAGE(&ui));

    if (status != EXIT_SUCCESS) {
      fprintf(stderr, "%s\n", status < 0 ? pigpio_error(status) : strerror(status));
    }

    if (pthread_mutex_lock(&m_running) == EXIT_SUCCESS) {
      _running = running;
      pthread_mutex_unlock(&m_running);
    }
  }

  status = finalize_ui(&ui);

  return status;
}


