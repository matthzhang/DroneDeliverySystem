#ifndef TIMER_DECORATOR_H_
#define TIMER_DECORATOR_H_

#include <vector>
#include "IStrategy.h"
#include "Stopwatch.hpp"
#include <fstream>

using std::ofstream;

class TimerDecorator: public IStrategy {
    public:
        ofstream f;
        TimerDecorator(IStrategy *strategy_) {
            strategy = strategy_;
            timeElapsed = 0;
            sw = stopwatch::Stopwatch();
            f.open("text.txt");
        }
        ~TimerDecorator(){
            f.close();
        }

        void Move(IEntity* entity, double dt);
        bool IsCompleted();
        stopwatch::Stopwatch sw;
    protected:
        IStrategy *strategy;
        int timeElapsed;
}; 

#endif
