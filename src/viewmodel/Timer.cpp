#include "Timer.h"

timer::timer()
{
    start_time= time(nullptr);
    time_data=0;
    is_pause=false;
}
time_t timer::show_time()
{
    time_t new_time=time(nullptr);
    time_data=new_time-start_time;
    return time_data;
}
void timer::pause_timing()
{
    time_t new_time=time(nullptr);//获取暂停时间
    time_data=new_time-start_time;//更新暂停前的时间之差
}
void timer::start_timing()
{
    start_time=time(nullptr)-time_data;
}

timer::~timer()
{
    
}