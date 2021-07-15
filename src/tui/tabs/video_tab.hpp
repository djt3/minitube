#ifndef _TABS_VIDEO_H_
#define _TABS_VIDEO_H_

#include "../../../videx/src/video.hpp"
#include "tab.hpp"

namespace tui {
  class video_tab : public tab {
  public:
    virtual void draw() override;
    virtual void process_input(char input) override;

    virtual std::string get_title() override = 0;

  protected:
    virtual std::string get_source_url() = 0;

    void refresh();

    bool m_refreshing = false;
    std::vector<videx::video> m_videos;
  };
} // namespace tui

#endif
