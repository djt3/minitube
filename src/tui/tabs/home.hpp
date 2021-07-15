#ifndef _TABS_HOME_H_
#define _TABS_HOME_H_

#include "video_tab.hpp"

namespace tui {
  class home : public video_tab {
  public:
    void draw() override;
    void process_input(char input) override;

    std::string get_title() override;

  protected:
    std::string get_source_url() override;
  };
}

#endif
