#include <string>
#include <vector>

namespace tui {
  class list_entry {
  public:
    list_entry(std::string left, std::string right) {
      m_left = left;
      m_right = right;
    }
    std::string m_left, m_right;
  };

  class tab {
  public:
    virtual void draw();

    virtual std::string get_title() {
      return "default title";
    }

    std::vector<list_entry> m_items;
  };
} // namespace tui
