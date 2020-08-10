#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "linux_system_spec.h"

using namespace std;
class System {
 public:
     System(LinuxSystemSpec);
     float Cpu();                   // TODO: See src/system.cpp
     std::vector<Process>& Processes();  // TODO: See src/system.cpp
     float MemoryUtilization();          
     long UpTime();                      
     long TotalProcesses();               
     long RunningProcesses();             
     string Kernel();               
     string OperatingSystem();      

  // TODO: Define any necessary private members
 private:
     LinuxSystemSpec linux_system_spec;
     string kernel;
     string operating_system;
     std::vector<Process> processes_ = {};
};

#endif