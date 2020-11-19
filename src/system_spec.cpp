#include "system_spec.h"


float SystemSpec::get_memory_utilization() {
	return 0.0;
}


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

float SystemSpec::get_cpu_utilization(int) { return 0.0; }
