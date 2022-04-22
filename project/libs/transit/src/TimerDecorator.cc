#include "TimerDecorator.h"

void TimerDecorator::start_timer(){
    sw.start();
}

float TimerDecorator::stop_timer(){
    timeElapsed = sw.elapsed();
    //timeElapsed = sw.elapsed();
    return timeElapsed;
}

bool TimerDecorator::IsCompleted(){
    return strategy->IsCompleted();
}

void TimerDecorator::Move(IEntity* entity, double dt){
    strategy->Move(entity, dt);
}