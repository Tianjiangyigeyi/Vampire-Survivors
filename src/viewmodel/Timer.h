#ifndef TIMER_H
#define TIMER_H

#include <time.h>
class timer
{
public:
    timer();
    ~timer();
    time_t show_time();
    void start_timing();
    void pause_timing();
private:
    time_t start_time;//开始计时的时间
    time_t pause_time;//暂停开始的时间
    time_t time_data;//实际时间间隔
    bool is_pause;
};
#endif