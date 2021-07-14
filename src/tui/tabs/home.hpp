#include "tab.hpp"
#include "../../../videx/src/video.hpp"


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
