#ifndef PROCESS_SPEC_H
#define PROCESS_SPEC_H
#include <string>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
using namespace std;
class ProcessSpec {
    public:
        virtual std::string get_command(int)=0;
        virtual string get_ram(int)=0;
        virtual std::string get_uid(int)=0;
        virtual std::string get_user(int)=0;
        virtual long int get_up_time(int)=0;
        virtual double get_cpu_utilization(int)=0;
};

#endif