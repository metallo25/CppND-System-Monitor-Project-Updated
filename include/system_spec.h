#ifndef SYSTEM_SPEC_H
#define SYSTEM_SPEC_H
#include <string>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <process.h>
using namespace std;
class SystemSpec {
    public:
        virtual float get_memory_utilization()=0;
        virtual long get_total_processes()=0;
        virtual long get_running_processes()=0;
        virtual string get_operating_system()=0;
        virtual string get_kernel()=0;
        virtual float get_cpu_utilization(int)=0;
};

#endif