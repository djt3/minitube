#include "tui.hpp"
#include "tabs/home.hpp"
#include "tabs/search.hpp"
#include "utils.hpp"

#include <chrono>
#include <iostream>
#include <mutex>
#include <sys/ioctl.h>
#include <thread>

std::vector<tui::tab *> tabs;
int tab_index = 0;

void tui::initialize() {
  utils::clear(true);
  utils::hide_cursor();
  utils::disable_input();

  tui::home *home_tab = new tui::home();
  tui::search *search_tab = new tui::search();

  tabs.push_back(home_tab);
  tabs.push_back(search_tab);
}

bool closing = false;
std::mutex mutex;

void input_loop() {
  while (!closing) {
    char input;
    read(0, &input, 1);

    mutex.lock();

    switch (input) {
    case 'q':
      tui::uninitialize();
      break;

    case 0x9: // tab
      tab_index++;
      tab_index %= tabs.size();
      tui::utils::clear(true);
      break;

    default:
      tabs[tab_index]->process_input(input);
      break;
    }

    mutex.unlock();
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

    mutex.lock();

    utils::clear();

    utils::print_line(tabs[tab_index]->get_title(), "", utils::color::black,
                      utils::color::white);

    utils::cursor_y++;

    tabs[tab_index]->draw();

    utils::move_cursor(0, utils::get_terminal_height());
    utils::print_line("hello left", "hello right", utils::color::black,
                      utils::color::white);

    mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
