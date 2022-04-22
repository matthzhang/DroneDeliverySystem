#ifndef TIMER_DECORATOR_H_
#define TIMER_DECORATOR_H_

#include <vector>
#include "IStrategy.h"
#include "Stopwatch.hpp"

class TimerDecorator: public IStrategy {
    public:
        TimerDecorator(IStrategy *strategy_) {
            strategy = strategy_;
            timeElapsed = 0;
            sw = Stopwatch();
        }

        void Move(IEntity* entity, double dt){}
        bool IsCompleted(){}
        virtual void start_timer(Stopwatch sw);
        virtual float stop_timer(Stopwatch sw);
    protected:
        IStrategy *strategy;
        Stopwatch sw;
        float timeElapsed;
}; 

#endif
