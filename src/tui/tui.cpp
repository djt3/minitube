#include "tui.hpp"
#include "tabs/tab.hpp"
#include "utils.hpp"

#include <iostream>

void tui::initialize() {
  utils::clear(true);
  utils::hide_cursor();
}

void tui::uninitialize() {
  utils::clear(true);
  utils::show_cursor();
}

tui::tab *active_tab = nullptr;

void tui::draw() {
  if (utils::get_terminal_height() < 2)
    return;

  utils::clear();

  std::cout << "hello\n";

  if (!active_tab)
    return;
}
