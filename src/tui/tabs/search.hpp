#ifndef _TABS_SEARCH_H_
#define _TABS_SEARCH_H_

#include "video_tab.hpp"
#include "../tui.hpp"

namespace tui {
  class search : public video_tab {
  public:
    void draw() override;
    void process_input(int input);

    std::string get_title() override;
    std::string get_source_url() override;

  private:
    bool m_in_results_view = false;
    std::string m_search_text = "";
    std::string m_search_text_previous = "";
  };
} // namespace tui

#endif
