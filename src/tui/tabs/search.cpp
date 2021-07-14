#include "search.hpp"

void tui::search::draw() {

  tab::draw();
}

void tui::search::process_input(char input) {
  switch (input) {
  default:
    tab::process_input(input);
    break;
  }
}

std::string tui::search::get_title() {
  return "search";
}
