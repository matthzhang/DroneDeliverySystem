#include "queue.h"

int main()
{
    // create a queue of capacity 5
    Queue q(5);

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "The front element is " << q.peek() << endl;

    cout << "need to dequeue " << q.indexOf(1) << " elements before 1 is at the front" << endl;
    cout << "need to dequeue " << q.indexOf(2) << " elements before 2 is at the front" << endl;
    cout << "need to dequeue " << q.indexOf(3) << " elements before 3 is at the front" << endl;
    cout << "need to dequeue " << q.indexOf(4) << " elements before 4 is at the front" << endl;

    q.dequeue();

    q.enqueue(4);

    cout << "The queue size is " << q.size() << endl;

    q.dequeue();
    q.dequeue();
    q.dequeue();

    if (q.isEmpty()) {
        cout << "The queue is empty\n";
    }
    else if (q.isFull()) {
        cout << "The queue is full\n";
    }
    else {
        cout << "The queue is not empty\n";
    }

    q.enqueue(24);
    q.enqueue(42);
    q.enqueue(38);
    q.enqueue(15);
    cout << "need to dequeue " << q.indexOf(15) << " elements before 15 is at the front" << endl;
    cout << "need to dequeue " << q.indexOf(38) << " elements before 38 is at the front" << endl;
    cout << "Running bubble sort algorithm: \n";
    q.bubbleSort();
    cout << "\n";
    q.clear();

    q.enqueue(24);
    q.enqueue(42);
    q.enqueue(38);
    q.enqueue(15);
    cout << "Running merge sort algorithm: \n";
    q.mergeSort();
    cout << "\n";
    q.clear();

    return 0;
}
