#include "home.hpp"
#include "../../../videx/src/videx.hpp"
#include "../utils.hpp"

#include <thread>

bool refreshing = false;

bool queue_playback = false;

void tui::home::draw() {
  if (!refreshing && m_items.empty()) {
    std::thread refresh_thread(&tui::home::refresh, this);
    refresh_thread.detach();
  }

  if (queue_playback) {
    queue_playback = false;
    system(("mpv \"https://www.youtube.com" + m_videos[m_selected_item].url +
            "\" > /dev/null")
               .c_str());

    // clear mpv text from the screen - force a redraw
    utils::clear(true);
  }

  tab::draw();
}

void tui::home::process_input(char input) {
  switch (input) {
  case 'r':
    refresh();
    break;

  case 0xA: // enter
    queue_playback =
        true; // queue the playback: we want it to lock the main draw thread
    break;

  default:
    tab::process_input(input);
    break;
  }
}

std::string tui::home::get_title() {
  if (refreshing)
    return "home - refreshing";

  else
    return "home";
}

void tui::home::refresh() {
  refreshing = true;

  m_items.clear();

  m_videos = videx::extract_videos("https://www.youtube.com/");

  for (videx::video &video : m_videos) {
    list_entry item = list_entry(video.title, video.channel);

    m_items.push_back(item);
  }

  refreshing = false;
}
