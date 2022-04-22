/******************************************************************************
csci3081 s22 hw3 part A
*******************************************************************************/

/******************************************************************************
Includes
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Define the default capacity of a queue
#define SIZE 1000

// A class to store a queue
class Queue
{
        int *arr;       // array to store queue elements
        int capacity;   // maximum capacity of the queue
        int front;      // front points to the front element in the queue (if any)
        int rear;       // rear points to the last element in the queue
        int count;      // current size of the queue

    public:
        Queue(int size = SIZE);     // constructor
        ~Queue();                   // destructor

        Queue(const Queue &q1);    // copy constructor
        Queue& operator=(const Queue& other); // assignment operator

        int dequeue();              // pop 0th element from the queue and return it
        void enqueue(int x);        // add a new element 'int x' to the end of the queue
        int peek();                 // look at 0th element from the queue (w.o removal) and return it
        int indexOf(int e);         // returns the index of the passed in val
        int size();                 // returns the current number of elements in the queue
        bool isEmpty();             // bool indicating whether the queue is empty
        bool isFull();              // bool indicating whether the queue is full
        int getCapacity();          // returns private member variable 'capacity'
        void clear();               // clears the contents of the queue, capacity stays the same, size changes
        void bubbleSort();          // bubble sort algo
        void mergeSort();           // merge sort algo

    private:
        void mergeSortHelper(int arr[], int l, int r);
        void mergeSortMerge(int arr[], int p, int q, int r);
};
