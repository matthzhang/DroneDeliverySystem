#include "TimerDecorator.h"
using std::ofstream;
using std::cout;

bool TimerDecorator::IsCompleted() {}

void TimerDecorator::Move(IEntity* entity, double dt) {
  if (strategy->IsCompleted()) {
    timeElapsed = sw.elapsed();
    cout << timeElapsed << ", " << entity->GetStrategyName() << "\n";
    f << timeElapsed << ", " << entity->GetStrategyName() << "\n";
  } else {
    strategy->Move(entity, dt);
  }
}