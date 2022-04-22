#include "gtest/gtest.h"
#include "queue.h"
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>

#define MAX_QUEUE_BYTES 24
#define START_CASE 0
#define FINAL_CASE 1000
typedef void (Queue::*Sort)();

/// NOTE: For better testing, could iterate from Queue objects with capacity 0 to 1000 for each test.
class QueueTest : public ::testing::Test {};

/***************************************************************************************************/
/***************************************** CONSTRUCTOR TESTING *************************************/
/***************************************************************************************************/

// Helper function for testing the constructor in the Queue class.
void constructor_tests(Queue queue, int size) {
  EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity was not initialized correctly";
  EXPECT_EQ(sizeof(queue), MAX_QUEUE_BYTES) << "Queue should take up 24 bytes in memory"; 
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    std::string output = testing::internal::GetCapturedStdout();
  }
  EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity was not initialized correctly";
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at it's capacity";
  EXPECT_EQ(sizeof(queue), MAX_QUEUE_BYTES) << "Queue should take up 24 bytes in memory";
  EXPECT_EQ(queue.isFull(), true) << "Queue should be full"; 
}

/*
  + Checks the constructor for the Queue class of the following tests:
  - CASES: Iterates from 0 to 1000 checking each Queue object construction.
*/
TEST_F(QueueTest, QueueConstructorTests) {
  for (int size = START_CASE; size <= FINAL_CASE; size++) {
    constructor_tests(Queue(size), size);
  }
}

/***************************************************************************************************/
/***************************************** DEQUEUE TESTING *****************************************/
/***************************************************************************************************/

// Helper function for testing the dequeue() function in the Queue class.
void dequeue_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Enqueue and dequeue in the same iteration, verify the dequeue() results.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();
    testing::internal::CaptureStdout();
    int top = queue.peek(), deq = queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(top, deq) << "Dequeued and peeked value should match";
    EXPECT_EQ(n, deq) << "Enqueued and dequeued value should match";
    EXPECT_EQ(output_de, "Removing " + to_string(n) + "\n") << "Dequeued output should match";
  }  
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated enqueuing and dequeuing.";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated enqueuing and dequeuing.";

  // Fill up the queue by enqueuing and check that the size() and isFull() functions reflect that.
  for (int i = 0; i < ARR_SIZE; i++) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i]);
    string output_en = testing::internal::GetCapturedStdout();
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing.";
  EXPECT_EQ(queue.isFull(), true) << "Queue is not full, possible to still enqueue.";

  // Begin dequeuing and verify the output matches what should be expected.
  queue_size = queue.size();
  for (int i = 0; i < queue_size; i++) {
    testing::internal::CaptureStdout();
    int top = queue.peek(), deq = queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(top, deq) << "Dequeued and peeked value should match";
    EXPECT_EQ(arr[i], deq) << "Dequeued value should match the corresponding element in the vector";
    EXPECT_EQ(output_de, "Removing " + to_string(deq) + "\n") << "Dequeued output should match";
  } 
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated dequeuing";

  // Verify that the dequeue() function will prompt a error if called on empty queue.
  testing::internal::CaptureStdout();
  EXPECT_EXIT(queue.dequeue(), testing::ExitedWithCode(1), "") << "Queue should not able to dequeue";
  string output_er = testing::internal::GetCapturedStdout();
}

/*
  + Checks the dequeue() function for the Queue class of the following tests:
  - CASE 1: Dequeuing from a empty Queue object.
  - CASE 2: Dequeuing from a Queue object given a capacity.
  - CASE 3: Dequeuing from a Queue object not given a capacity.
*/
TEST_F(QueueTest, QueueDequeueTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  dequeue_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  dequeue_tests(given_size, given_size.getCapacity());

  /// CASE 3
  dequeue_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** ENQUEUE TESTING *****************************************/
/***************************************************************************************************/

// Helper function for testing the enqueue() function in the Queue class.
void enqueue_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Enqueue and dequeue in the same iteration, verify the enqueue() results.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    int deq = queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();
    
    EXPECT_EQ(n, deq) << "Enqueued and dequeued values should match";
    EXPECT_EQ(output_en, "Inserting " + to_string(n) + "\n") << "Enqueued output should match";
  }  
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated enqueuing and dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated enqueuing and dequeuing";
  
  // Fill up the queue by enqueuing and verify the output matches what should be expected.
  for (int i = 0; i < ARR_SIZE; i++) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i]);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output_en, "Inserting " + to_string(arr[i]) + "\n") << "Enqueued output should match";
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing";
  EXPECT_EQ(queue.isFull(), true) << "Queue is not full, possible to still enqueue";

  // Verify that the enqueue() function will prompt a error if called on a full queue.
  testing::internal::CaptureStdout();
  EXPECT_EXIT(queue.enqueue(-1), testing::ExitedWithCode(1), "") << "Queue should not able to enqueue";
  string output_er = testing::internal::GetCapturedStdout();
}

/*
  + Checks the enqueue() function for the Queue class of the following tests:
  - CASE 1: Enqueuing to a Queue object with no capacity.
  - CASE 2: Enqueuing to a Queue object given a capacity.
  - CASE 3: Enqueuing to a Queue object not given a capacity.
*/
TEST_F(QueueTest, QueueEnqueueTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  enqueue_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  enqueue_tests(given_size, given_size.getCapacity());
  /// CASE 3
  enqueue_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** PEEK TESTING ********************************************/
/***************************************************************************************************/

// Helper function for testing the peek() function in the Queue class.
void peek_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Enqueue and dequeue in the same iteration, verify the peek() results.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    int top = queue.peek();

    testing::internal::CaptureStdout();
    int deq = queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(top, deq) << "Peeked and dequeued value should match";
  }  
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated enqueuing and dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated enqueuing and dequeuing";


  // Fill up the queue by enqueuing and verify the output matches what should be expected.
  for (int i = 0; i < ARR_SIZE; i++) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i]);
    string output_en = testing::internal::GetCapturedStdout();

    int top = queue.peek();
    EXPECT_EQ(top, arr[0]) << "Front element should match the peek while enqueuing";
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing";
  EXPECT_EQ(queue.isFull(), true) << "Queue is not full, possible to still enqueue";

  // Begin dequeuing and verify that the output matches what should be expected.
  queue_size = queue.size();
  for (int i = 0; i < queue_size; i++) {
    int top = queue.peek();
    testing::internal::CaptureStdout();
    int deq = queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(top, deq) << "Peeked and dequeued value should match";
  }
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated dequeuing";

  // Verify that the peek() function will prompt a error if called on empty queue.
  testing::internal::CaptureStdout();
  EXPECT_EXIT(queue.peek(), testing::ExitedWithCode(1), "") << "Queue should not able to peek";
  string output_er = testing::internal::GetCapturedStdout();

}

/*
  + Checks the peek() function for the Queue class of the following tests:
  - CASE 1: Peeking to a Queue object with no capacity.
  - CASE 2: Peeking to a Queue object given a capacity.
  - CASE 3: Peeking to a Queue object not given a capacity.
*/
TEST_F(QueueTest, QueuePeekTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  peek_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  peek_tests(given_size, given_size.getCapacity());

  /// CASE 3
  peek_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** INDEXOF TESTING *****************************************/
/***************************************************************************************************/

// Helper function for testing the indexOf() function in the Queue class.
void indexOf_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size, arr_offset = 1;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Enqueue and dequeue in the same iteration, verify the indexOf() results.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    int position = queue.indexOf(n);
    int notIn_position = queue.indexOf(-n);

    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(position, 0) << "Position should always be 0 before dequeuing for indexOf(n)";
    EXPECT_EQ(notIn_position, -1) << "Position should always be -1 before dequeuing for indexOf(-n) (not in queue)";
  }  
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated enqueuing and dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated enqueuing and dequeuing";

  // Fill up the queue by enqueuing and verify that the element is in the queue with indexOf().
  for (int i = 0; i < ARR_SIZE; i++) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i]);
    string output_en = testing::internal::GetCapturedStdout();
    for (int j = 0; j < i; j++) {
      EXPECT_EQ(queue.indexOf(arr[j]), j) << "Elements should match.";
    }
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing";
  EXPECT_EQ(queue.isFull(), true) << "Queue is not full, possible to still enqueue";
  
  // Begin dequeuing and verify that the output matches what should be expected.
  queue_size = queue.size();
  for (int i = 0; i < queue_size; i++) {
    testing::internal::CaptureStdout();
    int top = queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    for (int j = i + 1; j < ARR_SIZE; j++) {
      EXPECT_EQ(queue.indexOf(arr[j]), j - arr_offset) << "Element should be in the queue";
    }
    EXPECT_EQ(queue.indexOf(top), -1) 
    << "Element that was just dequeued should not be in the queue (no dupes given the input)";

    arr_offset++;
  }
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated dequeuing";

}

/*
  + Checks the indexOf() function for the Queue class of the following tests:
  - CASE 1: Getting index of a element in the Queue object with no capacity.
  - CASE 2: Getting index of a element in the to a Queue objects given a capacity.
*/
TEST_F(QueueTest, QueueIndexOfTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(5);
  Queue given_diff_size = Queue(10);

  /// CASE 1
  indexOf_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  indexOf_tests(given_size, given_size.getCapacity());
  indexOf_tests(given_diff_size, given_diff_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** SIZE TESTING ********************************************/
/***************************************************************************************************/

// Helper function for testing the size() function in the Queue class.
void size_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Enqueue and dequeue in the same iteration, verify the size() results.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.size(), 1) << "Queue should be a size of 1 after a enqueue";

    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.size(), 0) << "Queue should be empty after every enqueue & dequeue";
  } 
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated enqueuing and dequeuing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated enqueuing and dequeuing";


  // Fill up the queue by enqueuing and verify that the size is updated correctly.
  for (int i = 0; i < ARR_SIZE; i++) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i]);
    string output_en = testing::internal::GetCapturedStdout();
    EXPECT_EQ(queue.size(), i + 1) << "Queue's size should match the current index + 1 after a enqueue";
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing";
  EXPECT_EQ(queue.isFull(), true) << "Queue is not full, possible to still enqueue";

  // Begin dequeuing and verify that the output matches what should be expected.
  queue_size = queue.size();
  for (int i = 0; i < queue_size / 2; i++) {
    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.size(), queue_size - i - 1) << "Queue should be less than its last size by 1 after a dequeue.";
  }

  // Clear the queue and verify that the size is changed after the clearing.
  testing::internal::CaptureStdout();
  queue.clear();
  string output_cl = testing::internal::GetCapturedStdout();
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be 0 after repeated clearing";
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after repeated clearing";
}

/*
  + Checks the size() function for the Queue class of the following tests:
  - CASE 1: Checks the size of a Queue object with no capacity.
  - CASE 2: Checks the size of a Queue object with a given capacity.
  - CASE 3: Checks the size of a Queue object with no given capacity.
*/
TEST_F(QueueTest, QueueSizeTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  size_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  size_tests(given_size, given_size.getCapacity());

  /// CASE 3
  size_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** ISEMPTY TESTING *****************************************/
/***************************************************************************************************/

// Helper function for testing the isEmpty() function in the Queue class.
void isEmpty_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size, i = 0;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Enqueue and dequeue in the same iteration, verify the isEmpty() results.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.isEmpty(), false) << "Queue should not be empty after a enqueue";

    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after every enqueue & dequeue";
  } 

  // Fill up the queue by enqueuing and verify that its empty during this process.
  while (!queue.isFull() && size > 0) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i++]);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.isEmpty(), false) << "Queue should not be empty while enqueuing.";
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing";
  EXPECT_EQ(queue.isFull(), true) << "Queue is not full, possible to still enqueue";

  // Begin dequeuing and verify that the output matches what should be expected.
  while (!queue.isEmpty() && size > 0) {
    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();
    if (queue.size() > 0) {
      EXPECT_EQ(queue.isEmpty(), false) << "Queue should not be empty while dequeuing";
    }
  }
  EXPECT_EQ(queue.isEmpty(), true) << "Queue should be empty after dequeuing all";
}

/*
  + Checks the isEmpty() function for the Queue class of the following tests:
  - CASE 1: Checks if the Queue object with no capacity is empty.
  - CASE 2: Checks if the Queue object given a capacity is empty.
  - CASE 3: Checks if the Queue object not given a capacity is empty.
*/
TEST_F(QueueTest, QueueIsEmptyTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  isEmpty_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  isEmpty_tests(given_size, given_size.getCapacity());

  /// CASE 3
  isEmpty_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** ISFULL TESTING ******************************************/
/***************************************************************************************************/

// Helper function for testing the isFull() function in the Queue class.
void isFull_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size, i = 0;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Check enqueue and dequeue at the same time and check isFull()'s return value.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.isFull(), false) << "Queue should not be full after a single enqueue";

    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.isFull(), false) << "Queue should not be full after every enqueue & dequeue";
  } 

  // Fill up the queue by enqueuing and verify that its not full during this process.
  while (!queue.isFull() && size > 0) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i++]);
    string output_en = testing::internal::GetCapturedStdout();
    if (queue.size() < queue.getCapacity()) {
      EXPECT_EQ(queue.isFull(), false) << "Queue should not be full while enqueuing";
    }
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should be at capacity after repeated enqueuing";
  EXPECT_EQ(queue.isFull(), true) << "Queue is should be full after filling the queue";

  // Begin dequeuing and verify that the output matches what should be expected.
  while (!queue.isEmpty() && size > 0) {
    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();
    EXPECT_EQ(queue.isFull(), false) << "Queue should not be full while dequeuing";
  }
  if (size > 0) {
    EXPECT_EQ(queue.isFull(), false) << "Queue is should not be full after emptying the queue";
  }
}

/*
  + Checks the isFull() function for the Queue class of the following tests:
  - CASE 1: Checks if the Queue object with no capacity is full.
  - CASE 2: Checks if the Queue object given a capacity is full.
  - CASE 3: Checks if the Queue object not given a capacity is full.
*/
TEST_F(QueueTest, QueueIsFullTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  isFull_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  isFull_tests(given_size, given_size.getCapacity());

  /// CASE 3
  isFull_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** GETCAPACITY TESTING *************************************/
/***************************************************************************************************/

// Helper function for testing the getCapacity() function in the Queue class.
void getCapacity_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size, i = 0;
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Check enqueue and dequeue at the same time and check size()'s return value.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should not change after enqueuing";

    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should not change after every enqueue & dequeue";
  } 

  // Fill up the queue by enqueuing and verify the capacity.
  while (!queue.isFull()) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i++]);
    string output_en = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should not be changing while enqueuing";
  }
  EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should not have changed after repeated enqueuing";

  // Begin dequeuing and verify that the output matches what should be expected.
  while (!queue.isEmpty()) {
    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();

    EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should not be change while dequeuing";
  }
  EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should not have changed after repeated dequeuing";
}

/*
  + Checks the getCapacity() function for the Queue class of the following tests:
  - CASE 1: Checks if the Queue object with no capacity for its actual capacity.
  - CASE 2: Checks if the Queue object given a capacity for its actual capacity.
  - CASE 3: Checks if the Queue object not given a capacity for its actual capacity.
*/
TEST_F(QueueTest, QueueGetCapacityTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  getCapacity_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  getCapacity_tests(given_size, given_size.getCapacity());

  /// CASE 3
  getCapacity_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/***************************************** CLEAR TESTING *******************************************/
/***************************************************************************************************/

// Helper function for testing the clear() function in the Queue class.
void clear_tests(Queue& queue, int size) {
  const int ARR_SIZE = size; int queue_size, i = 0;
  string cleared = "";
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Check enqueue and clear instead of dequeuing, verify the clear's output works.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    queue.clear();
    string output_cl = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output_cl, "Removing " + to_string(n) + "\n") << "Clear's output should match";
  } 

  // While enqueuing and format that value that represents the clear() function's output.
  while (!queue.isFull()) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i]);
    string output_en = testing::internal::GetCapturedStdout();
    cleared += "Removing " + to_string(arr[i++]) + "\n";
  }
  EXPECT_EQ(queue.size(), size) << "Queue's size should match the capacity after filling up";
  EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should match the initialized capacity";

  testing::internal::CaptureStdout();
  queue.clear();
  string final_clear = testing::internal::GetCapturedStdout();

  EXPECT_EQ(final_clear, cleared) << "Outputed string from the clear() function should match the manually formatted one";
  EXPECT_EQ(queue.size(), 0) << "Queue's size should be reset back to 0 after clearing";
  EXPECT_EQ(queue.getCapacity(), size) << "Queue's capacity should have not changed after clearing";
}

/*
  + Checks the clear() function for the Queue class of the following tests:
  - CASE 1: Verifies the Queue object given a empty capacity is cleared.
  - CASE 2: Verifies the Queue object given a capacity is cleared.
  - CASE 3: Verifies the Queue object given a no capacity is cleared.
*/
TEST_F(QueueTest, QueueClearTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();

  /// CASE 1
  clear_tests(empty_queue, empty_queue.getCapacity());

  /// CASE 2
  clear_tests(given_size, given_size.getCapacity());

  /// CASE 3
  clear_tests(given_no_size, given_no_size.getCapacity());
}

/***************************************************************************************************/
/**********************************  BUBBLESORT & MERGESORT TESTING ********************************/
/***************************************************************************************************/

// Helper function for testing the mergeSort() and bubbleSort() functions in the Queue class.
void sort_tests(Queue& queue, int size, Sort alg) {
  const int ARR_SIZE = size; int queue_size, i = size - 1;
  string final_sort = "", sorted_output = "";
  // Sorting algorthirm that will be tested.
  auto queue_sort = mem_fn(alg);
  // Initializes vector of size N and fill it from values 1 to N.
  vector<int> arr(ARR_SIZE); iota(begin(arr), end(arr), 1);

  // Check enqueue, sort, then dequeue and verify the sorting's output is correct.
  for (int n = 1; n <= size; n++) {
    testing::internal::CaptureStdout();
    queue.enqueue(n);
    string output_en = testing::internal::GetCapturedStdout();

    testing::internal::CaptureStdout();
    queue_sort(queue);
    string output_bub = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output_bub, "Removing " + to_string(n) + "\nInserting " + to_string(n) + "\n") 
    << "Queue's sorting algorithm's output should match";

    testing::internal::CaptureStdout();
    queue.dequeue();
    string output_de = testing::internal::GetCapturedStdout();
  } 

  // Fill up the queue using the given array in reverse.
  while (!queue.isFull()) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i--]);
    string output_en = testing::internal::GetCapturedStdout();
  }

  // Format what the sorting algorithm should produce.
  for (int j = ARR_SIZE - 1; j >= 0; j--) {
    sorted_output += "Removing " + to_string(arr[j]) + "\n";
  }
  for (int j = 0; j < ARR_SIZE; j++) {
    sorted_output += "Inserting " + to_string(arr[j]) + "\n";
  }

  testing::internal::CaptureStdout();
  queue_sort(queue);
  final_sort = testing::internal::GetCapturedStdout();
  EXPECT_EQ(final_sort, sorted_output) << "Sorting output should match the manually formated output";

  // Reset the queue and prepare for another test.
  testing::internal::CaptureStdout();
  queue.clear();
  string output_cl = testing::internal::GetCapturedStdout();
  final_sort = ""; sorted_output = ""; i = size - 1;

  // Fill up the queue using the given array in reverse shuffled order.
  random_shuffle(arr.begin(), arr.end());
  while (!queue.isFull()) {
    testing::internal::CaptureStdout();
    queue.enqueue(arr[i--]);
    string output_en = testing::internal::GetCapturedStdout();
  }
  
  // Format what the sorting algorithm should produce.
  for (int j = ARR_SIZE - 1; j >= 0; j--) {
    sorted_output += "Removing " + to_string(arr[j]) + "\n";
  }
  sort(arr.begin(), arr.end());
  for (int j = 0; j < ARR_SIZE; j++) {
    sorted_output += "Inserting " + to_string(arr[j]) + "\n";
  }

  testing::internal::CaptureStdout();
  queue_sort(queue);
  final_sort = testing::internal::GetCapturedStdout();
  EXPECT_EQ(final_sort, sorted_output) << "Sorting output should match the manually formated output";
}

/*
  + Checks the bubbleSort() function for the Queue class of the following tests:
  - CASE 1: Checks if the Queue object with no capacity sorts correctly with bubbleSort.
  - CASE 2: Checks if the Queue object given different capacities sorts correctly with bubbleSort.
*/
TEST_F(QueueTest, QueueBubbleSortTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_diff_size = Queue(100);
  Sort alg = &Queue::bubbleSort;
  
  /// CASE 1
  sort_tests(empty_queue, empty_queue.getCapacity(), alg);

  /// CASE 2
  sort_tests(given_size, given_size.getCapacity(), alg);
  sort_tests(given_diff_size, given_diff_size.getCapacity(), alg);
}

/*
  + Checks the mergeSort() function for the Queue class of the following tests:
  - CASE 1: Checks if the Queue object with no capacity sorts correctly with mergeSort.
  - CASE 2: Checks if the Queue object given different capacities sorts correctly with mergeSort.
*/
TEST_F(QueueTest, QueueMergeSortTests) {
  Queue empty_queue = Queue(0);
  Queue given_size = Queue(10);
  Queue given_no_size = Queue();
  Sort alg = &Queue::mergeSort;

  /// CASE 1
  sort_tests(empty_queue, empty_queue.getCapacity(), alg);

  /// CASE 2
  sort_tests(given_size, given_size.getCapacity(), alg);

  /// CASE 3
  sort_tests(given_no_size, given_no_size.getCapacity(), alg);
}