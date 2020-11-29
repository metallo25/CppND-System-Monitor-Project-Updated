#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_process_spec.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int);
  int Pid();                              
  std::string User();                      
  std::string Command();                  
  float CpuUtilization();                  
  std::string Ram();                       
  long int UpTime();                       
  bool operator<(Process& a) ;  

  
 private:
 	LinuxProcessSpec linux_process_spec;
 	int process_id;
};

#endif