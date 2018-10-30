#ifndef __SERVO_UI__
#define __SERVO_UI__

#include <ncurses.h>

#define CURSOR_PERCENTAGE(ui_ptr) ((((ui_ptr)->cursor * 1.0)) / ((ui_ptr)->width - 4.0))

struct _ui_ {
  WINDOW* main_window;
  WINDOW* position_bar;

  size_t  height;
  size_t  width;

  int32_t x;
  int32_t y;

  int32_t cursor;
};

int32_t init_ui (struct _ui_*);
int32_t update_ui (struct _ui_*, int32_t);
int32_t finalize_ui (struct _ui_*);

#endif
