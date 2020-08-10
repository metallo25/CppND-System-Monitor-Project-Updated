#ifndef LINUX_PROCESS_SPEC_H
#define LINUX_PROCESS_SPEC_H
#include<process_spec.h>

class LinuxProcessSpec : public ProcessSpec {
    public:
    	std::string get_command(int) override;
        std::string get_ram(int) override;
        std::string get_uid(int) override;
        std::string get_user(int) override;
        long int get_up_time(int) override;
};

#endif