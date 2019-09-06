#include "format.h"
#include <iomanip>  // include for setw()
#include <string>
using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  int hour, min, sec;
  std::string hour_str, min_str, sec_str;
  std::string time_in_hh_mm_ss;

  // Calculate hours
  hour = seconds / 3600;

  // Calculate minutes
  seconds = seconds % 3600;
  min = seconds / 60;

  // Calculate seconds
  seconds = seconds % 60;
  sec = seconds;

  // Convert int to string
  hour_str = std::to_string(hour);
  min_str = std::to_string(min);
  sec_str = std::to_string(sec);

  // Set the field width to two and fill with zeros.
  std::ostringstream hh, mm, ss;
  hh << std::setw(2) << std::setfill('0') << hour_str;
  mm << std::setw(2) << std::setfill('0') << min_str;
  ss << std::setw(2) << std::setfill('0') << sec_str;

  // Join the string to get time in the format hh:mm:ss
  time_in_hh_mm_ss = hh.str() + ":" + mm.str() + ":" + ss.str();

  return time_in_hh_mm_ss;
}