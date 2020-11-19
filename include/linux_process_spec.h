#ifndef LINUX_PROCESS_SPEC_H
#define LINUX_PROCESS_SPEC_H
#include<process_spec.h>

class LinuxProcessSpec : public ProcessSpec {
    public:
    	std::string get_command(int) override;
        string get_ram(int) override;
        std::string get_uid(int) override;
        std::string get_user(int) override;
        long int get_up_time(int) override;
        double get_cpu_utilization(int) override;

    private:
    	std::map<std::string,std::string> _makeProcessInfoMap(int pid);
    	std::vector<std::string> _get_process_stat(int pid);
};

#endif