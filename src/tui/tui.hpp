#ifndef _TUI_H_
#define _TUI_H_

namespace tui {
  extern void initialize();
  extern void uninitialize();
  extern void run();
}

void setESC(bool input);
void moveTab(int input);

#endif
