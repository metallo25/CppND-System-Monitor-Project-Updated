#include "linux_process_spec.h"
#include "linux_system_spec.h"
#include "constants.h"
#include "iostream"

using std::string;
using std::to_string;

//Read and return the command associated with a process
string LinuxProcessSpec::get_command(int pid) {
    std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
    string line;
    std::getline(filestream, line);
    return line;

 }

//Read and return the memory used by a process
string LinuxProcessSpec::get_ram(int pid) { 
    string vm_size;
    string temp;
    auto process_info_map=this->_makeProcessInfoMap(pid); 
    auto vmsize_raw = process_info_map["VmSize:"];
    double vmsize = (vmsize_raw.length()==0) ? 0.0: (stod(vmsize_raw));
    vmsize = vmsize*0.001;
    return std::to_string(vmsize);

}

//Read and return the processes cpu utilization
double LinuxProcessSpec::get_cpu_utilization(int pid) {
    
    std::vector<std::string> process_time_reading = _get_process_stat(pid);

	double utime = stod(process_time_reading[13]);
    double stime = stod(process_time_reading[14]);
    double cutime = stod(process_time_reading[15]);
    double cstime = stod(process_time_reading[16]);
    double starttime = stod(process_time_reading[21]);
    double total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    
    double hertz =  sysconf(_SC_CLK_TCK);
    double seconds = LinuxSystemSpec::get_up_time() - (starttime / hertz);


    double cpu_usage = 100 * ((total_time / hertz) / seconds);
    return cpu_usage;


   }



//Read and return the user ID associated with a process
string LinuxProcessSpec::get_uid(int pid) { 
    
    auto process_info_map=this->_makeProcessInfoMap(pid);

    string uid;
    string temp;
    auto uid_info_line = process_info_map["Uid:"];
    std::istringstream linestream(uid_info_line);
    linestream >> uid >> temp;
    return uid;


 }
//Read and return the user associated with a process
string LinuxProcessSpec::get_user(int pid) { 

	auto expected_uid = this->get_uid(pid); 
    
    string user_name, uid, line,x;

    std::ifstream filestream(kPasswordPath);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
        	std::replace(line.begin(), line.end(), ':', ' ');
            std::istringstream linestream(line);
            linestream>>user_name>>x>>uid;
            if (uid==expected_uid)
            	return user_name;
        }

    }
    throw("Not able to find the user id:"+expected_uid);
    

}

//Read and return the uptime of a process
long LinuxProcessSpec::get_up_time(int pid) { 
    
    std::vector<std::string> process_time_reading = _get_process_stat(pid);

	double process_uptime = stod(process_time_reading[21]);

	double hertz =  sysconf(_SC_CLK_TCK);

	return process_uptime/hertz;

}


std::map<std::string, std::string> LinuxProcessSpec::_makeProcessInfoMap(int pid){
    string line;
    string key;
    string value;
    std::map<std::string, std::string> memory_info_map;
    std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key >> value) {
                memory_info_map.insert(std::make_pair(key, value));
            }
        }

    }
    return memory_info_map;
}


std::vector<std::string> LinuxProcessSpec::_get_process_stat(int pid){

	std::ifstream filestream(kProcDirectory+to_string(pid)+kStatFilename);
	std::vector<std::string> process_time_reading(22);
    if (filestream.is_open()) {
        string line;
        string name;
        
        std::getline(filestream, line);
        std::istringstream linestream(line);   
        linestream >> name >> process_time_reading[0]>>
                              process_time_reading[1]>>
                              process_time_reading[2]>>
                              process_time_reading[3]>>
                              process_time_reading[4]>>
                              process_time_reading[5]>>
                              process_time_reading[6]>>
                              process_time_reading[7]>>
                              process_time_reading[8]>>
                              process_time_reading[9]>>
                              process_time_reading[10]>>
                              process_time_reading[11]>>
                              process_time_reading[12]>>
                              process_time_reading[13]>>
                              process_time_reading[14]>>
                              process_time_reading[15]>>
                              process_time_reading[16]>>
                              process_time_reading[17]>>
                              process_time_reading[18]>>
                              process_time_reading[19]>>
                              process_time_reading[20]>>
                              process_time_reading[21];
        }
    return process_time_reading;
         
}