#include "TimerDecorator.h"
using std::ofstream;
using std::cout;

bool TimerDecorator::IsCompleted() {
  bool val = strategy->IsCompleted();
    if (val){
         timeElapsed = sw.elapsed();
         cout << timeElapsed << "\n";
        f << timeElapsed <<"\n";
    }
    return val;
}

void TimerDecorator::Move(IEntity* entity, double dt) {
    strategy->Move(entity, dt);
}