#ifndef TIMER_H_
#define TIMER_H_

#include <vector>
#include "TimerDecorator.h"
#include "IStrategy.h"
#include "Stopwatch.hpp"
class Timer: public TimerDecorator {
    public:
        void start_timer();
        float stop_timer();
}; 

#endif
