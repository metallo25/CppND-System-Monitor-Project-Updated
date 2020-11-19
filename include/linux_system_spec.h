#ifndef LINUX_SYSTEM_SPEC_H
#define LINUX_SYSTEM_SPEC_H
#include <process.h>
#include <system_spec.h>
#include <linux_process_spec.h>

class LinuxSystemSpec : public SystemSpec  {
    public:
        float get_memory_utilization() override;
        static long get_up_time() ;
        long get_total_processes() override;
        long get_running_processes() override;
        std::string  get_operating_system() override;
        std::string  get_kernel() override;
        float get_cpu_utilization(int id) override;
        vector<Process> get_all_processes();

    private:
    	std::map<std::string,std::string> _makeInfoMap(std::string);
    	double _getProcessorUtilization(std::string,std::string);

};

#endif