#include <iostream>
#include <math.h>

class Vector3 {
public:
  Vector3();
  Vector3(double x, double y, double z);

  Vector3 operator+(Vector3 vec);
  Vector3 operator-(Vector3 vec);
  Vector3 operator*(Vector3 vec);
  Vector3 operator/(Vector3 vec);

  Vector3 operator*(double s);
  Vector3 operator/(double s);

  void Print();

private:
  double x, y, z;
};
