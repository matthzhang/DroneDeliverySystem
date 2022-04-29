#include "TimerDecorator.h"
using std::ofstream;
using std::cout;

bool TimerDecorator::IsCompleted() {
  bool val = strategy->IsCompleted();
  if (val){
    int temp = sw.elapsed();
    timeElapsed = (temp - (temp %100)) / 1000.0;
    cout << timeElapsed << "\n";
    f << timeElapsed <<"\n";
    f.close();
  }
  return val;
}

void TimerDecorator::Move(IEntity* entity, double dt) {
    strategy->Move(entity, dt);
}