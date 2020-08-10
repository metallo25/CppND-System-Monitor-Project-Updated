#ifndef LINUX_SYSTEM_SPEC_H
#define LINUX_SYSTEM_SPEC_H
#include <system_spec.h>

class LinuxSystemSpec : public SystemSpec  {
    public:
        float get_memory_utilization() override;
        long get_up_time() override;
        std::vector<int> get_pids() override;
        long get_total_processes() override;
        long get_running_processes() override;
        std::string  get_operating_system() override;
        std::string  get_kernel() override;
        float get_cpu_utilization() override;

    private:
    	std::map<std::string,std::string> make_info_map(std::string);

};

#endif