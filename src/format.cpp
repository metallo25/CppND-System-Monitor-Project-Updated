#include <string>

#include "format.h"

using std::string;
using std::to_string;

string Format::ElapsedTime(long time_in_seconds) { 
    
    int hours = time_in_seconds/3600;
    int minutes = (time_in_seconds % 3600)/60;
    int seconds=(time_in_seconds % 3600)%60;

	return string(to_string(hours)+":"+to_string(minutes)+":"+to_string(seconds)); }