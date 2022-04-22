#ifndef TIMER_H_
#define TIMER_H_

#include <vector>
#include "TimerDecorator.h"
#include "IStrategy.h"

class Timer: public TimerDecorator {
    public:
        Timer(IStrategy *strategy_) {
            strategy = strategy_;
            timeElapsed = 0;
            sw = Stopwatch();
        }
        void start_timer(Stopwatch sw);
        float stop_timer(Stopwatch sw);
}; 

#endif
