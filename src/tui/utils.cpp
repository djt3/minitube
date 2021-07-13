#include "utils.hpp"

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

namespace tui::utils {
  void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);
  }

  void clear(bool full_clear) {
    fflush(stdout);

    if (full_clear) {
      system("clear");
    }

    else {
      move_cursor(0, 0);
    }

    fflush(stdout);
  }

  winsize get_terminal_size() {
    winsize size;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return size;
  }

  int get_terminal_width() {
    return static_cast<int>(get_terminal_size().ws_col);
  }

  int get_terminal_height() {
    return static_cast<int>(get_terminal_size().ws_row);
  }

  void set_text_color(e_color color) {
    printf("\u001b[%d;1m", color);
  }

  void set_background_color(e_color color) {
    printf("\u001b[%dm", static_cast<int>(color) + 10);
  }

  void reset() {
    printf("\u001b[0m");
  }

  void show_cursor() {
    system("setterm -cursor on");
  }

  void hide_cursor() {
    system("setterm -cursor off");
  }
} // namespace tui::utils
