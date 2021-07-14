#ifndef _TABS_HOME_H_
#define _TABS_HOME_H_

#include "../../../videx/src/video.hpp"
#include "tab.hpp"

namespace tui {
  class home : public tab {
  public:
    void draw() override;
    void process_input(char input) override;

    std::string get_title() override;

  private:
    void refresh();
    std::vector<videx::video> m_videos;
  };
} // namespace tui

#endif
