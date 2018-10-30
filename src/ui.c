#include "ui.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


int32_t init_ui (struct _ui_* ui) {
  if (ui != NULL) {

    initscr();

    start_color();
    cbreak();

    noecho();
    
    init_pair(1, COLOR_BLACK, COLOR_CYAN);

    memset(ui, 0, sizeof(struct _ui_));

    ui->main_window = stdscr;
    
    getmaxyx(stdscr, ui->height, ui->width);

    ui->x = 2;
    ui->y = (ui->height - 3) / 2;

    ui->position_bar = newwin(3, ui->width - 4, ui->y, ui->x);

    keypad(ui->position_bar, TRUE);
    keypad(ui->main_window, TRUE);

    ui->cursor = (ui->width - 4) / 2;

    box(ui->position_bar, 0, 0);

    wattron(ui->position_bar, COLOR_PAIR(1));
      mvwprintw(ui->position_bar, 1, ui->cursor, "O");
    wattroff(ui->position_bar, COLOR_PAIR(1));

    wrefresh(ui->main_window);
    wrefresh(ui->position_bar);

    return EXIT_SUCCESS;
  } else {
    return EINVAL;
  }
}

int32_t update_ui (struct _ui_* ui, int32_t delta_x) {
  if (ui != NULL) {
    int32_t new_cursor = ui->cursor + delta_x;
    if (0 < new_cursor && new_cursor < (ui->width - 4)) {
    
      mvwprintw(ui->position_bar, 1, ui->cursor, " ");

      wattron(ui->position_bar, COLOR_PAIR(1));
        mvwprintw(ui->position_bar, 1, new_cursor, "O");
      wattroff(ui->position_bar, COLOR_PAIR(1));

      wrefresh(ui->position_bar);
      refresh();

      ui->cursor = new_cursor;

    }
    return EXIT_SUCCESS;
  } else {
    return EINVAL;
  }
}

int32_t finalize_ui (struct _ui_* ui) {
  endwin(); 
}


