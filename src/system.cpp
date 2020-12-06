#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_system_spec.h"
#include "process.h"
#include "system.h"
#include <iostream>

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(LinuxSystemSpec linux_system_spec) : linux_system_spec(linux_system_spec){
}

float System::Cpu(int id) { return this->linux_system_spec.get_cpu_utilization(id); }

vector<Process> System::Processes() { 
	return this->linux_system_spec.get_all_processes(); }

std::string System::Kernel() { return this->linux_system_spec.get_kernel(); }

float System::MemoryUtilization() { return this->linux_system_spec.get_memory_utilization(); }

std::string System::OperatingSystem() { return this->linux_system_spec.get_operating_system(); }

long System::RunningProcesses() { return this->linux_system_spec.get_running_processes(); }

long System::TotalProcesses() { return this->linux_system_spec.get_total_processes(); }

int System::TotalProcessors() { return this->linux_system_spec.get_num_cpu_processors();}

long System::UpTime() { return LinuxSystemSpec::get_up_time(); }