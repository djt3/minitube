#include "video_tab.hpp"
#include "../../../videx/src/videx.hpp"
#include "../utils.hpp"

#include <thread>

void tui::video_tab::draw() {
  if (!m_refreshing && m_items.empty()) {
    std::thread refresh_thread(&tui::video_tab::refresh, this);
    refresh_thread.detach();
  }

  tab::draw();
}

void tui::video_tab::process_input(int input) {
  switch (-input) {
  case 'r':
    refresh();
    break;

  case 0xA: // enter
    system(("nohup mpv \"https://www.youtube.com" + m_videos[m_selected_item].url +
            "\" >/dev/null 2>&1 &")
               .c_str());

    // clear mpv text from the screen - force a redraw
    utils::clear(true);
    break;

  default:
    tab::process_input(input);
    break;
  }
}

void tui::video_tab::refresh() {
  m_refreshing = true;

  m_items.clear();

  m_videos = videx::extract_videos(get_source_url());

  for (videx::video &video : m_videos) {
    list_entry item = list_entry(video.title, video.channel);

    m_items.push_back(item);
  }

  m_refreshing = false;
}
