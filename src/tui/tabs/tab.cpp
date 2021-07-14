#include "tab.hpp"
#include "../utils.hpp"

void tui::tab::draw() {
  int terminal_height = utils::get_terminal_height();

  for (int i = 0; i < m_items.size(); i++) {
    if (i > terminal_height - 1)
      break;

    utils::move_cursor(0, utils::cursor_y + 1);

    if (i == m_selected_item) {
      utils::print_line(m_items[i].m_left, m_items[i].m_right, utils::color::black, utils::color::white);
    } else {
      utils::print_line(m_items[i].m_left, m_items[i].m_right, utils::color::white, utils::color::black);
    }
  }
}

std::string tui::tab::get_title() {
  return "default title";
}

void tui::tab::process_input(char input) {
  switch (input) {
  case 'j':
    if (m_selected_item < m_items.size() - 1)
      m_selected_item++;
    break;
  case 'k':
    if (m_selected_item > 0)
      m_selected_item--;
    break;
  }
}
