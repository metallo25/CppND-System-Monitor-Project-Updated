#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "linux_process_spec.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int process_id) {
	this->process_id=process_id;
}

int Process::Pid() { 
	return this->process_id; }

// Return this process's CPU utilization
float Process::CpuUtilization() { return this->linux_process_spec.get_cpu_utilization(this->process_id); }

// Return the command that generated this process
string Process::Command() { return this->linux_process_spec.get_command(this->process_id); }

// Return this process's memory utilization
string Process::Ram() { return this->linux_process_spec.get_ram(this->process_id); }

string Process::User() { return this->linux_process_spec.get_user(this->process_id); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return this->linux_process_spec.get_up_time(this->process_id); }

// Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }
