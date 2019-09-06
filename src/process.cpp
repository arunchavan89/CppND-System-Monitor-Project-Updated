#include <unistd.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() { return m_pid; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() {
  std::string line, value;
  int count = 0;
  float utime, stime, cutime, cstime, starttime, uptime, total_time, seconds;  

  std::ifstream file_for_cpu_uilization(LinuxParser::kProcDirectory +
                                        std::to_string(m_pid) +
                                        LinuxParser::kStatFilename);
  if (file_for_cpu_uilization.is_open()) {
    while (std::getline(file_for_cpu_uilization, line)) {
      std::istringstream linestream(line);
      while (linestream >> value) {
        count++;
        /*https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599*/

        if (count == 13) {
          utime = std::stol(value);
        }
        if (count == 14) {
          stime = std::stol(value);
        }
        if (count == 15) {
          cutime = std::stol(value);
        }
        if (count == 16) {
          cstime = std::stol(value);
        }
        if (count == 21) {
          starttime = std::stol(value);
        }

        uptime = UpTime();

        total_time = utime + stime + cutime + cstime;

        seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));

        if (seconds == 0) {
          return 0.0f;
        }
        m_cpu_utilization =
            (100.0 * ((total_time / sysconf(_SC_CLK_TCK)) / seconds));
      }
    }
  }

  return m_cpu_utilization;
}

// DONE: Return the command that generated this process
string Process::Command() {
  std::string line;
  std::ifstream file_for_command(LinuxParser::kProcDirectory +
                                 std::to_string(m_pid) +
                                 LinuxParser::kCmdlineFilename);
  if (file_for_command.is_open()) {
    std::getline(file_for_command, line);
    m_command = line;
  }

  return m_command;
}

// DONE: Return this process's memory utilization
string Process::Ram() {
  std::string line, key, value;
  std::ifstream file_for_ram(LinuxParser::kProcDirectory +
                             std::to_string(m_pid) +
                             LinuxParser::kStatusFilename);
  if (file_for_ram.is_open()) {
    while (std::getline(file_for_ram, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "VmSize:") {
        m_ram = value;
        return m_ram;
      }
    }
  }

  return m_ram;
}

// DONE: Return the user (name) that generated this process
string Process::User() {
  std::string line, key, value;
  std::ifstream file_for_user_info(LinuxParser::kProcDirectory +
                                   std::to_string(m_pid) +
                                   LinuxParser::kStatusFilename);
  if (file_for_user_info.is_open()) {
    while (std::getline(file_for_user_info, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        m_user = value;
        return m_user;
      }
    }
  }

  return m_user;
}

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() {
  std::string line, value;
  int count = 0;
  std::ifstream file_for_up_time(LinuxParser::kProcDirectory +
                                 std::to_string(m_pid) +
                                 LinuxParser::kStatFilename);
  if (file_for_up_time.is_open()) {
    while (std::getline(file_for_up_time, line)) {
      std::istringstream linestream(line);
      while (linestream >> value) {
        count++;
        /*get 22th value in /proc/pid/stat
         * http://man7.org/linux/man-pages/man5/proc.5.html */
        if (count == 22) {
          
          m_up_time = std::stol(value);
          //std::cout << "value = "<< value;
          m_up_time = m_up_time / sysconf(_SC_CLK_TCK);
        }
      }
    }
  }

  return m_up_time;
}
// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }