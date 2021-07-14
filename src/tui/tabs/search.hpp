#ifndef _TABS_SEARCH_H_
#define _TABS_SEARCH_H_

#include "../../../videx/src/video.hpp"
#include "tab.hpp"

namespace tui {
  class search : public tab {
  public:
    void draw() override;
    void process_input(char input) override;

    std::string get_title() override;

  private:
    std::vector<videx::video> m_videos;
  };
} // namespace tui

#endif
