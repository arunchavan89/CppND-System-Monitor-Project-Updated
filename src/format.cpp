#include <string>
#include "format.h"

using std::string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) 
{ 
    long hour, min, sec;
    std::string hour_str, min_str, sec_str;
    std::string time_in_hh_mm_ss;

    // Get HH
    hour = seconds/3600;
	
    // Get MM
    seconds = seconds%3600;
	min = seconds/60;

    // Get SS
	seconds = seconds%60;	
    if(seconds%60 == 0)
    {
        sec = 60;  
    }
    else
    {
        sec = seconds;
    }
    
    hour_str = std::to_string(hour);
    min_str = std::to_string(min);
    sec_str = std::to_string(sec);

    time_in_hh_mm_ss =  hour_str + ":" + min_str  + ":" + sec_str + "\n"; 
    
    return time_in_hh_mm_ss; 
}