#ifndef _TABS_TAB_H_
#define _TABS_TAB_H_

#include <string>
#include <vector>

namespace tui {
  class list_entry {
  public:
    list_entry() = default;

    list_entry(std::string left, std::string right) {
      m_left = left;
      m_right = right;
    }
    std::string m_left, m_right;
  };

  class tab {
  public:
    virtual void draw();

    virtual std::string get_title();

    virtual void process_input(char input);

    int m_scroll_offset = 0;
    int m_selected_item = 0;
    std::vector<list_entry> m_items;
  };
} // namespace tui

#endif
