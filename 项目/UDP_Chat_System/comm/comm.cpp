#include "comm.h"

void print_log(const std::string& msg, const std::string& fun, const int& line)
{
#ifdef _PRINT_LOG_
    std::cerr<<"[ "<<fun<<":"<<line<<" ]"<<" "<<msg<<std::endl;
#endif
}

void print_debug(const std::string& msg)
{
#ifdef _PRINT_DEBUG_
    std::cout<<msg<<std::endl;
#endif
}
