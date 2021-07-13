#include "tab.hpp"

namespace tui {
  class home : public tab {
  public:
    void draw();

    std::string get_title() override;
  };
} // namespace tui
