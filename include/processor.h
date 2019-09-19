#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // DONE: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  float m_user;
  float m_nice;
  float m_system;
  float m_idle;
  float m_iowait;
  float m_irq;
  float m_softirq;
  float m_steal;
  float total_cpu_time_since_boot;
  float total_cpu_idel_time_since_boot;
  float total_cpu_usage_time_since_boot;
  float total_cpu_percentage;
};

#endif