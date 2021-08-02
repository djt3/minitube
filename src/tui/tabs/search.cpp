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

    std::string search_box = "[" + m_search_text + "_";
    search_box.resize(search_width - 1, ' ');
    search_box += ']';

    printf("%s", search_box.c_str());
   
  }
}

void tui::search::process_input(int input) {
  if (m_in_results_view) {
    if (input == -'b') {
      m_in_results_view = false;
    }

    else {
	  video_tab::process_input(input);
    }
  }

  else {
    setESC(false);
    if (input == 0xA) {
    	m_in_results_view = true;
	utils::clear(true);
	setESC(true);
	m_search_text_previous = m_search_text;
	video_tab::refresh();
    }
    else if (input == 127){
    	if(!m_search_text.length()){
		setESC(true);
		if(!m_search_text_previous.length()){
			moveTab(-1);
		}else{
    			m_in_results_view = true;
			utils::clear(true);
			m_search_text = m_search_text_previous;
		}
	}else if(m_search_text.length() > 0){
		m_search_text.pop_back();	
	}
    }
    else if (input > 31){
    	m_search_text += input;
    }
  }
}

std::string tui::search::get_title() {
  return m_refreshing ? "search - refreshing" : "search: "+m_search_text;
}

std::string tui::search::get_source_url() {
  std::string search_url = "https://www.youtube.com/results?search_query=" + m_search_text;

  std::replace(search_url.begin(), search_url.end(), ' ', '+');

  return search_url;
}
