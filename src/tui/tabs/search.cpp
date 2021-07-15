#include "search.hpp"
#include "../utils.hpp"

void tui::search::draw() {
  if (m_in_results_view) {
    video_tab::draw();
  }

  else {
    int terminal_width = utils::get_terminal_width();
    int terminal_height = utils::get_terminal_height();

    utils::set_text_color(utils::color::white);
    utils::set_background_color(utils::color::black);

    int search_width = terminal_width * .8f;
    search_width += search_width % 2;

    utils::move_cursor((terminal_width - search_width) * .5f,
                       terminal_height * .5f);

    std::string search_box = "[" + m_search_text;
    search_box.resize(search_width - 1, ' ');
    search_box += ']';

    printf("%s", search_box.c_str());
  }
}

void tui::search::process_input(char input) {
  if (m_in_results_view) {
    if (input == 'b') {
      m_in_results_view = false;
    }

    else {
      video_tab::process_input(input);
    }
  }

  else {
    if (input == 0xA) {
      m_in_results_view = true;
      utils::clear(true);
    }

    else {
      m_search_text += input;
    }
  }
}

std::string tui::search::get_title() {
  return m_refreshing ? "search - refreshing" : "search";
}

std::string tui::search::get_source_url() {
  std::string search_url = "https://www.youtube.com/results?search_query=" + m_search_text;

  std::replace(search_url.begin(), search_url.end(), ' ', '+');

  return search_url;
}
