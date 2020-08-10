
#include "linux_system_spec.h"
#include "constants.h"
#include <iostream>
using std::stof;
using std::string;
using std::to_string;
using std::vector;



// TODO: Read and return the system memory utilization
float LinuxSystemSpec::get_memory_utilization() {
    auto memory_info_map=this->make_info_map(kProcDirectory+kMeminfoFilename);
    auto memory_free=stol(memory_info_map["MemFree:"]);
    auto memory_total=stol(memory_info_map["MemTotal:"]);
    auto memory_usage = (static_cast<double>(memory_total)-static_cast<double>(memory_free))/static_cast<double>(memory_total);
    return memory_usage; 
}

// TODO: Read and return the system uptime
long LinuxSystemSpec::get_up_time() {
    std::ifstream filestream(kProcDirectory+kUptimeFilename);
    if (filestream.is_open()) {
        string line;
        string up_time,idle_time;
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> up_time >> idle_time;
        return stol(up_time);
  }

}

// needs to be moved linux_process_spec
vector<int> LinuxSystemSpec::get_pids(){

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
  return pids;
    
    
};

// TODO: Read and return the total number of processes
long LinuxSystemSpec::get_total_processes() {
  auto process_info_map=this->make_info_map(kProcDirectory+kStatFilename);
  return stol(process_info_map["processes"]);
};

// TODO: Read and return the number of running processes
long LinuxSystemSpec::get_running_processes() {
  auto process_info_map=this->make_info_map(kProcDirectory+kStatFilename);
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

// TODO: Read and return CPU utilization
float LinuxSystemSpec::get_cpu_utilization() { return {}; }


std::map<std::string, std::string> LinuxSystemSpec::make_info_map(string path){
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
