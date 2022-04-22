#include "queue.h"

// Constructor to initialize a queue
Queue::Queue(int size)
{
    arr = new int[size];
    capacity = size;
    front = 0;
    rear = -1;
    count = 0;
}

// Destructor to free memory allocated to the queue
Queue::~Queue() {
    delete[] arr;
}

Queue::Queue(const Queue &q1) {
    capacity = q1.capacity;
    front = q1.front;
    rear= q1.rear;
    count = q1.count;
    arr = new int[q1.capacity];
    for (int i = 0; i < q1.capacity; i++) {
      arr[i] = q1.arr[i];
    }
}

Queue& Queue::operator=(const Queue& other) {
    if (this != &other) {
        int* new_array = new int[other.capacity];
        std::copy(other.arr, other.arr + other.capacity, new_array);
        delete[] arr;
        this->arr = new_array;
        this->count = other.count;
        this->rear = other.rear;
        this->capacity = other.capacity;
        this->front = other.front;
    }
    return *this;
}

// Utility function to dequeue the front element
int Queue::dequeue()
{
    // check for queue underflow
    if (isEmpty())
    {
        std::cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }

    int x = arr[front];
    std::cout << "Removing " << x << endl;

    front = (front + 1) % capacity;
    count--;

    return x;
}

// Utility function to add an item to the queue
void Queue::enqueue(int item)
{
    // check for queue overflow
    if (isFull())
    {
        std::cout << "Overflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Inserting " << item << endl;

    rear = (rear + 1) % capacity;
    arr[rear] = item;
    count++;
}

// Utility function to return the front element of the queue
int Queue::peek()
{
    if (isEmpty())
    {
        std::cout << "Underflow\nProgram Terminated\n";
        exit(EXIT_FAILURE);
    }
    return arr[front];
}

// Utility function to return how far back a particular element is in the queue, returns -1 if e not in queue
int Queue::indexOf(int e) {
    if(isEmpty()){
        return -1;
    }
    int ret = 0;
    for(int i = front; i != rear; i = (i+1)%capacity) {
        if(arr[i] == e)
            return ret;
        ret++;
    }
    return arr[rear] == e ? ret : -1;
}

// Utility function to return the size of the queue
int Queue::size() {
    return count;
}

// Utility function to check if the queue is empty or not
bool Queue::isEmpty() {
    return (size() == 0);
}

// Utility function to check if the queue is full or not
bool Queue::isFull() {
    return (size() == capacity);
}

int Queue::getCapacity() {
    return capacity;
}

void Queue::clear() {
    if (isEmpty()) {
        return;
    }
    while (front != rear) { // remove all elements until front matches rear
        int x = arr[front];
        std::cout << "Removing " << x << endl;

        front = (front + 1) % capacity;
        count--;
    }
    // remove final element
    int x = arr[front];
    std::cout << "Removing " << x << endl;

    front = (front + 1) % capacity;
    count--;
}

void Queue::bubbleSort() {
    int temp_arr[count];  // create temp array to store elements
    int temp_capacity = 0;
    while (!isEmpty()) {  // dequeue all elements in queue into the temp array
        temp_arr[temp_capacity] = dequeue();
        temp_capacity++;
    }

    // Following bubble sort from https://www.programiz.com/dsa/bubble-sort:
    // loop to access each array element
    for (int step = 0; step < temp_capacity - 1; ++step) {

        // loop to compare array elements
        for (int i = 0; i < temp_capacity - step - 1; ++i) {

            // compare two adjacent elements
            // change > to < to sort in descending order
            if (temp_arr[i] > temp_arr[i + 1]) {

                // swapping occurs if elements
                // are not in the intended order
                int temp = temp_arr[i];
                temp_arr[i] = temp_arr[i + 1];
                temp_arr[i + 1] = temp;
            }
        }
    }

    for (int i = 0; i < temp_capacity; i++) {
        enqueue(temp_arr[i]);
    }
}

void Queue::mergeSort() {
    int temp_arr[count];  // create temp array to store elements
    int temp_capacity = 0;
    while (!isEmpty()) {  // dequeue all elements in queue into the temp array
        temp_arr[temp_capacity] = dequeue();
        temp_capacity++;
    }

    mergeSortHelper(temp_arr, 0, temp_capacity - 1);

    for (int i = 0; i < temp_capacity; i++) {
        enqueue(temp_arr[i]);
    }
}

// Following merge sort function from: https://www.geeksforgeeks.org/merge-sort/
/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void Queue::mergeSortHelper(int arr[], int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSortHelper(arr, l, m);
        mergeSortHelper(arr, m + 1, r);

        mergeSortMerge(arr, l, m, r);
    }
}

// Following merge sort function from: https://www.geeksforgeeks.org/merge-sort/
void Queue::mergeSortMerge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
    are any */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
    are any */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
