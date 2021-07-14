#include "tui.hpp"
#include "tabs/home.hpp"
#include "utils.hpp"

#include <chrono>
#include <iostream>
#include <sys/ioctl.h>
#include <thread>

tui::tab *active_tab = nullptr;

void tui::initialize() {
  utils::clear(true);
  utils::hide_cursor();
  utils::disable_input();

  active_tab = new home();
}

bool closing = false;

void input_loop() {
  while (!closing) {
    char input;
    read(0, &input, 1);

    if (input == 'q') {
      tui::uninitialize();
      return;
    }

    else if (active_tab) {
      active_tab->process_input(input);
    }
  }
}

void tui::uninitialize() {
  utils::clear(true);
  utils::show_cursor();
  utils::enable_input();

  closing = true;
}

void tui::run() {
  int last_dimensions = 0;

  std::thread input_thread(input_loop);
  input_thread.detach();

  while (!closing) {
    if (utils::get_terminal_height() < 2)
      return;

    winsize size = utils::get_terminal_size();
    int dimensions = size.ws_col % size.ws_row + size.ws_row;

    if (dimensions != last_dimensions) {
      last_dimensions = dimensions;
      utils::clear(true);
    }

    utils::clear();

    if (!active_tab)
      continue;

    utils::print_line(active_tab->get_title(), "", utils::color::black,
                      utils::color::white);

    utils::cursor_y++;

    active_tab->draw();

    utils::move_cursor(0, utils::get_terminal_height());
    utils::print_line("hello left", "hello right", utils::color::black,
                      utils::color::white);

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
