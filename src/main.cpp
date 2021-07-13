#include <chrono>
#include <thread>
#include <iostream>

#include "tui/tui.hpp"

int main() {
  tui::initialize();

  while (true) {
    tui::draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
