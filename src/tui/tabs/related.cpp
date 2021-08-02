#include "related.hpp"

void tui::related::draw() {
  video_tab::draw();
}

void tui::related::process_input(int input) {
	if(input == 'c'){
		//close tab
	}else{
		video_tab::process_input(input) ;
	}
}

std::string tui::related::get_title() {
 return m_refreshing ? "related videos - refreshing" : video_url; 
}

std::string tui::related::get_source_url() {
 return video_url; 
}
