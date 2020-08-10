#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "linux_system_spec.h"
#include "process.h"
#include "system.h"


using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System(LinuxSystemSpec linux_system_spec) : linux_system_spec(linux_system_spec){
}

// TODO: Return the system's CPU
float System::Cpu() { return this->linux_system_spec.get_cpu_utilization(); }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

std::string System::Kernel() { return this->linux_system_spec.get_kernel(); }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return this->linux_system_spec.get_memory_utilization(); }

std::string System::OperatingSystem() { return this->linux_system_spec.get_operating_system(); }

// TODO: Return the number of processes actively running on the system
long System::RunningProcesses() { return this->linux_system_spec.get_running_processes(); }

// TODO: Return the total number of processes on the system
long System::TotalProcesses() { return this->linux_system_spec.get_total_processes(); }

// TODO: Return the number of seconds since the system started running
long System::UpTime() { return this->linux_system_spec.get_up_time(); }