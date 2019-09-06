#include "linux_parser.h"
#include <dirent.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
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
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, number;  // Adding a variable 'number' to get the version
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel >> number;
  }
  return kernel + ' ' + number;  // Get the kernel + number
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  if (DIR* directory = opendir(kProcDirectory.c_str())) {
    while (struct dirent* file = readdir(directory)) {
      // Is this a directory?
      if (file->d_type == DT_DIR) {
        // Is every character of the name a digit?
        string filename(file->d_name);
        if (std::all_of(filename.begin(), filename.end(), isdigit)) {
          int pid = stoi(filename);
          pids.push_back(pid);
        }
      }
    }
    closedir(directory);
  }

  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  float total_memory = 0.0f;
  float free_memory = 0.0f;
  float total_memory_used = 0.0f;

  // Read file from /proc/meminfo
  std::ifstream file_for_memoryinfo(kProcDirectory + kMeminfoFilename);

  if (file_for_memoryinfo.is_open()) {
    while (std::getline(file_for_memoryinfo, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;

      if (key == "MemTotal:") {
        total_memory = stof(value);
      }

      if (key == "MemFree:") {
        free_memory = stof(value);
      }
    }
  }
  // https://stackoverflow.com/questions/41224738/how-to-calculate-system-memory-usage-from-proc-meminfo-like-htop/41251290#41251290
  // Total used memory = MemTotal - MemFree
  total_memory_used = total_memory - free_memory;

  return total_memory_used;
}

// DONE: Read and return the system uptime
long int LinuxParser::UpTime() {
  std::string line;
  std::string uptime_of_the_system;
  std::string time_spent_in_the_idle_process;
  long uptime = 0;
  // Information about system up time exists in the /proc/uptime file.
  std::ifstream file_for_up_time(kProcDirectory + kUptimeFilename);

  if (file_for_up_time.is_open()) {
    std::getline(file_for_up_time, line);
    std::istringstream linestream(line);
    linestream >> uptime_of_the_system >> time_spent_in_the_idle_process;
    uptime = std::stol(uptime_of_the_system.c_str());
  }

  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  std::string line, key1;
  int total_num_processes = 0;
  // Information about the total number of processes on the system exists in the
  // /proc/stat file
  std::ifstream file_for_num_running_processes(kProcDirectory + kStatFilename);
  if (file_for_num_running_processes.is_open()) {
    while (std::getline(file_for_num_running_processes, line)) {
      std::istringstream linestream(line);
      linestream >> key1 >> total_num_processes;
      if (key1 == "processes") {
        return total_num_processes;
      }
    }
  }

  return total_num_processes;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  std::string line, key1;
  int num_processes = 0;
  // Information about the number of processes on the system that are currently
  // running exists in the /proc/stat file
  std::ifstream file_for_num_running_processes(kProcDirectory + kStatFilename);
  if (file_for_num_running_processes.is_open()) {
    while (std::getline(file_for_num_running_processes, line)) {
      std::istringstream linestream(line);
      linestream >> key1 >> num_processes;
      if (key1 == "procs_running") {
        return num_processes;
      }
    }
  }

  return num_processes;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }