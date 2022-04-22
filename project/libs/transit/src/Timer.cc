#include "Timer.h"

void Timer::start_timer(){
    sw.start();
}

float Timer::stop_timer(){
    timeElapsed = sw.elapsed();
    //timeElapsed = sw.elapsed();
    return timeElapsed;
}