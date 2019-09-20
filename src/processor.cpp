#include "processor.h"
#include <fstream>
#include <iostream>
#include <string>
#include "linux_parser.h"
// DONE: Return the aggregate CPU utilization

/*
Total CPU time since boot = user + nice + system + idle + iowait + irq + softirq
+ steal

Total CPU Idle time since boot = idle + iowait

Total CPU usage time since boot = Total CPU time since boot - Total CPU Idle
time since boot

Total CPU percentage = Total CPU usage time since boot/Total CPU time since boot
X 100
*/
float Processor::Utilization() {
  std::string line, value;
  int count = 0;
  std::ifstream file_for_CPU_utilization(LinuxParser::kProcDirectory +
                                         LinuxParser::kStatFilename);
  if (file_for_CPU_utilization.is_open()) {
    std::getline(file_for_CPU_utilization, line);
    // std::cout << "line = " << line << std::endl;
    std::istringstream linestream(line);
    while (linestream >> value) {
      if (count == 1) {
        m_user = std::stof(value);
      }

      if (count == 2) {
        m_nice = std::stof(value);
      }

      if (count == 3) {
        m_system = std::stof(value);
      }

      if (count == 4) {
        m_idle = std::stof(value);
      }

      if (count == 5) {
        m_iowait = std::stof(value);
      }

      if (count == 6) {
        m_irq = std::stof(value);
      }

      if (count == 7) {
        m_softirq = std::stof(value);
      }

      if (count == 8) {
        m_steal = std::stof(value);
      }

      count++;
    }

    total_cpu_time_since_boot = m_user + m_nice + m_system + m_idle + m_iowait +
                                m_irq + m_softirq + m_steal;
    total_cpu_idel_time_since_boot = m_idle + m_iowait;
    total_cpu_usage_time_since_boot =
        total_cpu_time_since_boot - total_cpu_idel_time_since_boot;
    total_cpu_percentage =
        (total_cpu_usage_time_since_boot / total_cpu_time_since_boot);
  }
  return total_cpu_percentage;
}