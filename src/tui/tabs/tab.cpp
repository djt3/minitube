#include "tab.hpp"
#include "../tui.hpp"
#include "../utils.hpp"

void tui::tab::draw() {
  int terminal_height = utils::get_terminal_height();

  for (int i = m_scroll_offset; i < m_scroll_offset + std::min(terminal_height - 2, static_cast<int>(m_items.size())); i++) {
    utils::move_cursor(0, utils::cursor_y + 1);

    if (i == m_selected_item) {
      utils::print_line(m_items[i].m_left, m_items[i].m_right,
                        utils::color::black, utils::color::white);
    } else {
      utils::print_line(m_items[i].m_left, m_items[i].m_right,
                        utils::color::white, utils::color::black);
    }
  }

}

std::string tui::tab::get_title() {
  return "default title";
}

void tui::tab::process_input(int input) {
  switch (-input) {
  case 'j':
    m_selected_item++;
    break;
  case 'k':
    m_selected_item--;
    break;
  }

  if (m_selected_item < 0) {
    m_selected_item = m_items.size() - 1;
  } else if (m_selected_item >= m_items.size()) {
    m_selected_item = 0;
  }

  int terminal_height = utils::get_terminal_height();

  int scroll_start=0;

  if (m_items.size() >= terminal_height - 2) {
    while (terminal_height - m_selected_item + m_scroll_offset <= 2) {
      m_scroll_offset++;
    }
    
    while (m_selected_item < m_scroll_offset) {
      m_scroll_offset--;
    }
  } else {
    m_scroll_offset = 0;
  }
}
