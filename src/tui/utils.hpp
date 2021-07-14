#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

struct winsize;

namespace tui::utils {
  enum class color : int {
    black = 30,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
  };

  extern int cursor_x, cursor_y;

  extern void move_cursor(int x, int y);
  extern void move_cursor_by(int x, int y);
  extern void clear(bool full_clear = false);
  extern winsize get_terminal_size();
  extern int get_terminal_width();
  extern int get_terminal_height();
  extern void set_text_color(color color);
  extern void set_background_color(color color);
  extern void reset();

  extern void show_cursor();
  extern void hide_cursor();

  extern void enable_input();
  extern void disable_input();

  extern void print_text(const std::string& text, color text_color = color::white, color background_color = color::black);
  extern void print_line(const std::string& left_text, const std::string& right_text, color text_color = color::white, color background_color = color::black);
} // namespace tui::utils

#endif
