#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "linux_system_spec.h"
#include "linux_process_spec.h"

using namespace std;
class System {
 public:
     System(LinuxSystemSpec);
     float Cpu(int);                   
     std::vector<Process> Processes(); 
     float MemoryUtilization();          
     long UpTime();                      
     long TotalProcesses();               
     long RunningProcesses();             
     string Kernel();               
     string OperatingSystem();
     int TotalProcessors();    

  // TODO: Define any necessary private members
 private:
     LinuxSystemSpec linux_system_spec;
     LinuxProcessSpec linux_process_spec;
     string kernel;
     string operating_system;
};

#endif