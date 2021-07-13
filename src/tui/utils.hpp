struct winsize;

namespace tui::utils {
  enum class e_color : int {
    black = 30,
    red,
    green,
    yellow,
    blue,
    magenta,
    cyan,
    white
  };

  extern void move_cursor(int x, int y);
  extern void clear(bool full_clear = false);
  extern winsize get_terminal_size();
  extern int get_terminal_width();
  extern int get_terminal_height();
  extern void set_text_color(e_color color);
  extern void set_background_color(e_color color);
  extern void reset();
  extern void show_cursor();
  extern void hide_cursor();
} // namespace tui::utils
