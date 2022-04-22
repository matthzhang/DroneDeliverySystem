#include "vector3.h"

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(Vector3 vec) {
  return Vector3(x + vec.x, y + vec.y, z + vec.z);
}
Vector3 Vector3::operator-(Vector3 vec) {
  return Vector3(x - vec.x, y - vec.y, z - vec.z);
}
Vector3 Vector3::operator*(Vector3 vec) {
  return Vector3(x * vec.x, y * vec.y, z * vec.z);
}
Vector3 Vector3::operator/(Vector3 vec) {
  return Vector3(x / vec.x, y / vec.y, z / vec.z);
}

Vector3 Vector3::operator*(double s) { return Vector3(x * s, y * s, z * s); }
Vector3 Vector3::operator/(double s) { return Vector3(x / s, y / s, z / s); }

void Vector3::Print() {
  std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}
