#include "TimerDecorator.h"
#include <iostream>

bool TimerDecorator::IsCompleted(){
    bool val = strategy->IsCompleted();
    if (val){
        std::cout << sw.elapsed() << std::endl;
    }
    return val;
}

void TimerDecorator::Move(IEntity* entity, double dt){
    strategy->Move(entity, dt);
}

void TimerDecorator::Reset(){
   sw.start();
}