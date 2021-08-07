#include "home.hpp"

void tui::home::draw() {
  video_tab::draw();
}

void tui::home::process_input(int input) {
 video_tab::process_input(input) ;
}

std::string tui::home::get_title() {
 return m_refreshing ? "home - refreshing" : "home"; 
}

std::string tui::home::get_source_url() {
 return "https://www.youtube.com/"; 
}
