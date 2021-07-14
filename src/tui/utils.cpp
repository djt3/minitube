#include "utils.hpp"

#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

namespace tui::utils {
  int cursor_x, cursor_y;

  void move_cursor(int x, int y) {
    printf("\033[%d;%dH", y, x);

    cursor_x = x;
    cursor_y = y;
  }

  void move_cursor_by(int x, int y) {
    x = cursor_x + x;
    y = cursor_y + y;

    printf("\033[%d;%dH", y, x);

    move_cursor(x, y);
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

  void set_text_color(color color) {
    printf("\u001b[%d;1m", static_cast<int>(color));
  }

  void set_background_color(color color) {
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

  void enable_input() {
    struct termios term_attrs = {0};
    tcgetattr(0, &term_attrs);

    term_attrs.c_cc[VMIN] = 1;
    term_attrs.c_cc[VTIME] = 0;
    term_attrs.c_lflag |= ICANON;
    term_attrs.c_lflag |= ECHO;

    tcsetattr(0, TCSANOW, &term_attrs);
  }

  void disable_input() {
    struct termios term_attrs = {0};
    tcgetattr(0, &term_attrs);

    term_attrs.c_lflag &= ~ICANON;
    term_attrs.c_lflag &= ~ECHO;
    term_attrs.c_cc[VMIN] = 1;
    term_attrs.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &term_attrs);
  }

  void print_text(const std::string &text, color text_color,
                  color background_color) {
    set_text_color(text_color);
    set_background_color(background_color);

    std::cout << text << std::endl;
  }

  int last_dimensions = 0;
  std::vector<int> color_cache;
  std::vector<std::pair<std::string, std::string>> line_cache;

  int draw_count = 0;

  void clear(bool full_clear) {
    set_text_color(color::white);
    set_background_color(color::black);

    fflush(stdout);

    if (full_clear) {
      system("clear");

      // force all lines to be redrawn
      last_dimensions = 0;
    }

    else {
      move_cursor(0, 0);
    }

    fflush(stdout);
  }

  void print_line(const std::string &left_text, const std::string &right_text,
                  color text_color, color background_color) {

    winsize size = get_terminal_size();

    int color =
        static_cast<int>(text_color) % static_cast<int>(background_color) + static_cast<int>(background_color);
    int dimensions = size.ws_col % size.ws_row + size.ws_row;

    // size of the terminal changed, refresh the cache
    if (dimensions != last_dimensions) {
      last_dimensions = dimensions;

      line_cache.clear();
      line_cache.resize(size.ws_row + 1);
      color_cache.resize(size.ws_row + 1);
    }

    // draw call is idential to cached one
    else if (line_cache[cursor_y].first == left_text &&
             line_cache[cursor_y].second == right_text &&
             color_cache[cursor_y] == color) {
      return;
    }

    line_cache[cursor_y].first = left_text;
    line_cache[cursor_y].second = right_text;

    color_cache[cursor_y] = color;

    set_text_color(text_color);
    set_background_color(background_color);

    move_cursor(0, cursor_y);

    int terminal_width = get_terminal_width();

    std::string dummy = "";
    dummy.resize(terminal_width, ' ');

    printf("%s", dummy.c_str());

    move_cursor(0, cursor_y);

    printf("%s", left_text.c_str());

    move_cursor(terminal_width - right_text.length() + 1, cursor_y);

    printf("%s", right_text.c_str());

    fflush(stdout);
    draw_count++;
  }
} // namespace tui::utils
