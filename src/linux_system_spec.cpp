#include <cassert>
#include <iostream>

#include "linux_system_spec.h"
#include "constants.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;



float LinuxSystemSpec::get_memory_utilization() {
    auto memory_info_map=this->_makeInfoMap(kProcDirectory+kMeminfoFilename);
    auto memory_free=stol(memory_info_map["MemFree:"]);
    auto memory_total=stol(memory_info_map["MemTotal:"]);
    auto memory_usage = (static_cast<double>(memory_total)-static_cast<double>(memory_free))/static_cast<double>(memory_total);
    return memory_usage; 
}

long LinuxSystemSpec::get_up_time() {
    std::ifstream filestream(kProcDirectory+kUptimeFilename);
    string up_time,idle_time;
    if (filestream.is_open()) {
        string line;
        
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> up_time >> idle_time;
  }
  return stol(up_time);

}

long LinuxSystemSpec::get_total_processes() {
  auto process_info_map=this->_makeInfoMap(kProcDirectory+kStatFilename);
  return stol(process_info_map["processes"]);
};

// TODO: Read and return the number of running processes
long LinuxSystemSpec::get_running_processes() {
  auto process_info_map=this->_makeInfoMap(kProcDirectory+kStatFilename);
  return stol(process_info_map["procs_running"]);
};

string LinuxSystemSpec::get_operating_system() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
    
};

string LinuxSystemSpec::get_kernel() {
  string os, kernel, dummy_string;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> dummy_string >>kernel;
  }
  return kernel;
    
};


//  Read and return CPU utilization
float LinuxSystemSpec::get_cpu_utilization(int id) { 
    string processor_name = (id==0) ? "cpu" : ("cpu"+to_string(id-1));
    return this->_getProcessorUtilization((kProcDirectory+kStatFilename),processor_name); }

// Return a container composed of the system's processes
vector<Process> LinuxSystemSpec::get_all_processes() {
    
  vector<int> pids;
  std::string s="/proc/";
  DIR* directory = opendir(s.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), [](auto i){return isdigit(i);})){
          int pid = stoi(filename);
          pids.push_back(pid);
      }
    }
  }
  closedir(directory);

  vector<Process> processes = {};
  for (auto pid : pids) {
      processes.push_back(Process(pid));
    }
  
  return processes;
}

std::map<std::string, std::string> LinuxSystemSpec::_makeInfoMap(string path){
    string line;
    string key;
    string value;
    std::map<std::string, std::string> memory_info_map;
    std::ifstream filestream(path);
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

double LinuxSystemSpec::_getProcessorUtilization(string path, string processor_name){
    std::ifstream filestream(path);
    double result=0.0;
    if (filestream.is_open()) {
        string line;
        string name;
        std::vector<std::string> processor_time_reading(10);
        std::getline(filestream, line);
        
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
        
            if(line.find(processor_name)!=string::npos){
                linestream >> name >> processor_time_reading[0]>>
                                      processor_time_reading[1]>>
                                      processor_time_reading[2]>>
                                      processor_time_reading[3]>>
                                      processor_time_reading[4]>>
                                      processor_time_reading[5]>>
                                      processor_time_reading[6]>>
                                      processor_time_reading[7]>>
                                      processor_time_reading[8]>>
                                      processor_time_reading[9]; 

                float user_time=stod(processor_time_reading[0])- stod(processor_time_reading[8]);
                float nice_time= stod(processor_time_reading[1])- stod(processor_time_reading[9]);
                float idle_all_time= stod(processor_time_reading[3])+stod(processor_time_reading[4]);
                float system_all_time=stod(processor_time_reading[2])+stod(processor_time_reading[5]+processor_time_reading[6]);
                float virtall_time=stod(processor_time_reading[8]) + stod(processor_time_reading[9]);
                float total_time= user_time+nice_time+system_all_time+idle_all_time+stod(processor_time_reading[7])+virtall_time;
                result= ((total_time-idle_all_time)/total_time);
                }
          }
    throw(("Processor name invalid:"+(processor_name)));

    }
  return result;
};


  
    
 
