#include "tab.hpp"

namespace tui {
  class home : public tab {
  public:
    void draw() override;

    std::string get_title() override;
  };
} // namespace tui
