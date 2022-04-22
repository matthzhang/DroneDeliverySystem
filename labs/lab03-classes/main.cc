/**
Includes Vector3 header class
some systems might need "../Vector3.h"
mine needs :  #include "lab3/Vector3.h"
*/
#include "vector3.h"
#include <iostream>
using namespace std;

int main(int argc, char**argv) {
  // this is how to print in cpp
  cout << "CSCI3081W Lab 3" << endl;

  // Default constructor and constructor with parameters
  Vector3 vector1 = Vector3();
  Vector3 vector2 = Vector3(1,1,1);
  Vector3 vector3 = Vector3(3,4,5);

  // Print
  cout << "Vector 1 contains the following: " << endl;
  vector1.Print();
  cout << "Vector 2 contains the following: " << endl;
  vector2.Print();
  cout << "Vector 3 contains the following: " << endl;
  vector3.Print();

  // Addition
  Vector3 vector4 = vector2 + vector3;
  cout << "Vector 4 contains the following: " << endl;
  vector4.Print();

  // Subtraction
  Vector3 vector5 = vector3 - vector2;
  cout << "Vector 5 contains the following: " << endl;
  vector5.Print();

  // Multiplication
  Vector3 vector6 = vector3*3;
  cout << "Vector 6 contains the following: " << endl;
  vector6.Print();

  // Division
  Vector3 vector7 = vector3/2;
  cout << "Vector 7 contains the following: " << endl;
  vector7.Print();

  // Euler's Integration Example
  Vector3 position = Vector3();
  Vector3 velocity = Vector3(1.0, 1.0, 0.0);
  float dt = 0.1;
  cout << "Initial Position: ";
  position.Print();
  cout << "Velocity: ";
  velocity.Print();
  cout << "dt: "<< dt << endl;
  for (int i = 0; i < 10; i++) {
    position = position + velocity * dt;
    cout << "Position at i=" << i << ": ";
    position.Print();
  }
}
