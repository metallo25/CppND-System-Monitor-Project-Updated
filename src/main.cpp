#include "ncurses_display.h"
#include "system_spec.h"
#include "linux_system_spec.h"
#include "system.h"
#include <iostream>

int main() {
  LinuxSystemSpec s1;
  std::cout<<s1.get_kernel();
  System system(s1);
  NCursesDisplay::Display(system);
}