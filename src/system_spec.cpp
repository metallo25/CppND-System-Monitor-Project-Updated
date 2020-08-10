#include "system_spec.h"


float SystemSpec::get_memory_utilization() {
	return 0.0;
}

long SystemSpec::get_up_time() {
	return 0.0;
}

vector<int> SystemSpec::get_pids(){ 
   return {0};   
};

long SystemSpec::get_total_processes() {
	return 0;
};

long SystemSpec::get_running_processes() {
	return 0;
};

string SystemSpec::get_operating_system() {
	return "";
};

string SystemSpec::get_kernel() {
	return "";
};

float SystemSpec::get_cpu_utilization() { return 0.0; }
