#ifndef _TABS_SEARCH_H_
#define _TABS_SEARCH_H_

#include "video_tab.hpp"

namespace tui {
  class related : public video_tab {
  public:
    void draw() override;
    void process_input(int input);

    std::string get_title() override;
    std::string get_source_url() override;

    std::string video_url = "";
  };
} // namespace tui

#endif
