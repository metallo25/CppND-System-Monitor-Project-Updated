#include "ncurses_display.h"
#include "system_spec.h"
#include "linux_system_spec.h"
#include "system.h"
#include <iostream>

int main() {
  LinuxSystemSpec s1;
  System system(s1);
  NCursesDisplay::Display(system,60);
}