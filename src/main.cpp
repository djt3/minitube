#include "tui/tui.hpp"

#include <iostream>
#include <signal.h>

int main() {
  signal(SIGINT, [](int sig) { tui::uninitialize(); });

  tui::initialize();

  tui::run();

  return 0;
}
