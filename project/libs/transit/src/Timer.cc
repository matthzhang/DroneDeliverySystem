#include "Timer.h"

void Timer::start_timer(Stopwatch sw){
    sw.start();
}

int Timer::stop_timer(Stopwatch sw){
    timeElapsed = sw.elapsed();
    return timeElapsed
}