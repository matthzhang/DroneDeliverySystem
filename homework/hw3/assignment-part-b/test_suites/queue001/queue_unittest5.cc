#include "gtest/gtest.h"
#include "queue.h"
#include <climits>
#include <algorithm>
#include <iterator>

// i am so sorry in advance for
// anyone who has to read
// this lol - welcome to extremely overfit unit tests in which I mix and match functions for bad reasons

class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
    default_q  = new Queue();
    one_q      = new Queue(1);
    overflow_q = new Queue(INT_MAX); // INT_MAX + 1?
    float_q    = new Queue(1000.2);
  }
  void TearDown() {
    delete default_q;
    delete one_q;
    delete overflow_q;
    delete float_q;
  }
 protected:
    Queue *default_q;
    Queue *one_q;
    Queue *overflow_q;
    Queue *float_q;
};

TEST_F(QueueTest, CopyAssignTest) {
  int copy_random_capacity = rand() % 576 + 1;
  
  Queue copy_q = Queue(copy_random_capacity);
  Queue copy_copy_q;
  int true_val[copy_random_capacity];
  EXPECT_EQ(copy_q.getCapacity(), copy_random_capacity)    << "Error: wrong rand queue capacity";
  EXPECT_EQ(copy_q.size(), 0)                << "Error: wrong rand queue size";
  EXPECT_EQ(copy_q.isEmpty(), true)          << "Error: wrong rand queue emptiness";
  EXPECT_EQ(copy_q.isFull(), false)          << "Error: wrong rand queue fullness";
  EXPECT_EQ(copy_q.indexOf(0), -1)           << "Error: indexOf on empty rand queue";
  
  /*

  // fill some parts of queue, array
  int len = rand() % random + 1;
  for (int i = 0; i < len; i++) {
    val = rand() % 575 + 1;
    true_val[i] = val;
    copy_q.enqueue(val);
  }

  // assignment!
  cout << "Now copying." << endl;
  copy_copy_q = copy_q;
  for (int i = 0; i < len; i++) {
    val = true_val[i];
    EXPECT_EQ(copy_copy_q.getCapacity(), random); // capacity
    EXPECT_EQ(copy_copy_q.size(), len - i); // count
    EXPECT_EQ(copy_copy_q.isEmpty(), false);
    EXPECT_EQ(copy_copy_q.isFull(), false);
    EXPECT_EQ(copy_copy_q.peek(), true_val[i]); // check front
    copy_copy_q.dequeue();

    EXPECT_NE(&copy_copy_q, &copy_q);
  }
  */
  for (int i = 0; i < copy_random_capacity - 1; i++) {
    true_val[i] = rand() % 575 + 1;
    copy_q.enqueue(true_val[i]);
  }

  // assignment!
  cout << "Now copying." << endl;
  copy_copy_q = copy_q;
  for (int i = 0; i < copy_random_capacity - 1; i++) {
    EXPECT_EQ(copy_copy_q.getCapacity(), copy_random_capacity); // capacity
    EXPECT_EQ(copy_copy_q.size(), copy_random_capacity - i - 1); // count
    EXPECT_EQ(copy_copy_q.isEmpty(), false);
    EXPECT_EQ(copy_copy_q.isFull(), false);
    EXPECT_EQ(copy_copy_q.peek(), true_val[i]); // check front
    copy_copy_q.dequeue();

    EXPECT_NE(&copy_copy_q, &copy_q);
  }
}

TEST_F(QueueTest, SizeOneTest) {
  EXPECT_EQ(one_q->isEmpty(), true)  << "Error: checking emptiness on empty queue";
  EXPECT_EQ(one_q->isFull(), false)  << "Error: checking fullness on empty queue";

  // test for overflow
  one_q->enqueue(1);
  EXPECT_EXIT(one_q->enqueue(2),
    testing::ExitedWithCode(1), "")  << "Error: overflow to a queue not found";

  EXPECT_EQ(one_q->isEmpty(), false) << "Error: checking emptiness on full 1 queue";
  EXPECT_EQ(one_q->isFull(), true)   << "Error: checking fullness on full 1 queue";
}

TEST_F(QueueTest, EmptyInitTest) {
  EXPECT_EQ(default_q->size(), 0)   << "Error: initialized queue size";
  EXPECT_EQ(Queue(12).size(), 0)    << "Error: initialized queue size; capacity 12";
  EXPECT_EQ(Queue(1503).size(), 0)  << "Error: initialized queue size; capacity 1503";
  EXPECT_EQ(one_q->size(), 0)       << "Error: initialized queue size; capacity 1"; 
  EXPECT_EQ(overflow_q->size(), 0)  << "Error: initialized queue size; capacity at INT_MAX"; 
  EXPECT_EQ(float_q->size(), 0)     << "Error: initialized queue size; capacity 1000 from float"; 
}

TEST_F(QueueTest, InitDefaultCapacityTest) {
  EXPECT_EQ(default_q->getCapacity(), 1000)      << "Error: wrong default queue capacity";
  EXPECT_EQ(Queue(12).getCapacity(), 12)         << "Error: wrong queue capacity 12";
  EXPECT_EQ(Queue(0).getCapacity(), 0)         << "Error: wrong queue capacity 0";
  EXPECT_EQ(Queue(1503).getCapacity(), 1503)     << "Error: wrong queue capacity 1503";
  EXPECT_EQ(one_q->getCapacity(), 1)             << "Error: wrong queue capacity 1"; 
  EXPECT_EQ(overflow_q->getCapacity(), INT_MAX)  << "Error: wrong queue capacity at INT_MAX"; 
  EXPECT_EQ(float_q->getCapacity(), 1000)        << "Error: wrong queue capacity 1000 from float";
}

TEST_F(QueueTest, EnqueueDequeueTest) {
  for (int i = 0; i < default_q->getCapacity(); i++) {
    default_q->enqueue(i + 3);
    if (default_q->peek() != 3 || default_q->size() != i + 1 ||
       default_q->isEmpty() || default_q->indexOf(i + 3) != i) {
        FAIL() << "peek/size/isEmpty/indexOf incorrect following enqueue";
    }
  }

  EXPECT_EQ(default_q->isFull(), true) << "Error: checking fullness on full default queue";
  EXPECT_EXIT(default_q->enqueue(1000),
    testing::ExitedWithCode(1), "")  << "Error: overflow to a queue not found";
    
  for (int i = 0; i < default_q->getCapacity(); i++) {
    if (default_q->peek() != i + 3) {
      FAIL() << "Error: peek incorrect following dequeue: " << default_q->peek() << " | " << i;
    } else if (default_q->size() != 1000 - i) {
      FAIL() << "Error: size incorrect following dequeue" << default_q->size();
    } else if (default_q->isEmpty()) {
      FAIL() << "Error: isEmpty falsely true following dequeue";
    } else if (default_q->indexOf(i + 3) != 0) {
      FAIL() << "Error: indexOf incorrect following dequeue";
    }
    default_q->dequeue();
  }
}

TEST_F(QueueTest, DequeueEmptyTest) {
  // test for underflow
  EXPECT_EXIT(default_q->dequeue(),
    testing::ExitedWithCode(1), "") << "Error: exit code not 1 dequeueing empty queue";

  default_q->enqueue(13);
  EXPECT_EQ(default_q->size(), 1)   << "Error: size after 1 queued element";

  int value = default_q->dequeue();
  EXPECT_EQ(value, 13)              << "Error: dequeue() on value 13 for 1 queued element";
  EXPECT_EQ(default_q->size(), 0)   << "Error: size after dequeuing last element";
  
  // test for underflow
  EXPECT_EXIT(default_q->dequeue(),
    testing::ExitedWithCode(1), "") << "Error: exit code not 1 dequeueing empty queue";
}

// CUT ONE

// TODO - add loop, reduce redundancy
TEST_F(QueueTest, EmptyRandomTest) {
  for (int i = 0; i < 15; i++) {
    int random = rand() % 3000 + 1; // get value in range 1-3000
    Queue q = Queue(random);

    EXPECT_EQ(q.getCapacity(), random)    << "Error: wrong rand queue capacity";
    EXPECT_EQ(q.size(), 0)                << "Error: wrong rand queue size";
    EXPECT_EQ(q.isEmpty(), true)          << "Error: wrong rand queue emptiness";
    EXPECT_EQ(q.isFull(), false)          << "Error: wrong rand queue fullness";
    EXPECT_EQ(q.indexOf(0), -1)           << "Error: indexOf on empty rand queue";

    EXPECT_EXIT(q.dequeue(),
    testing::ExitedWithCode(1), "")       << "Error: dequeueing empty rand queue";
    EXPECT_EXIT(q.peek(),
    testing::ExitedWithCode(1), "")       << "Error: peeking empty rand queue";

    q.clear();
    EXPECT_EQ(q.isEmpty(), true)          << "Error: wrong rand queue emptiness after clear";
    EXPECT_EQ(q.isFull(), false)          << "Error: wrong rand queue fullness after clear";
    EXPECT_EQ(q.getCapacity(), random)    << "Error: wrong rand queue capacity after clear";
    EXPECT_EQ(q.size(), 0)                << "Error: wrong rand queue size after clear";

    EXPECT_EXIT(q.dequeue(),
    testing::ExitedWithCode(1), "")       << "Error: dequeueing empty rand queue after clear";
    EXPECT_EXIT(q.peek(),
    testing::ExitedWithCode(1), "")       << "Error: peeking empty rand queue after clear";
    EXPECT_EQ(q.indexOf(0), -1)           << "Error: indexOf on empty rand queue after clear";

    q.bubbleSort();
    EXPECT_EQ(q.isEmpty(), true)          << "Error: wrong rand queue emptiness after bubbleSort";
    EXPECT_EQ(q.isFull(), false)          << "Error: wrong rand queue fullness after bubbleSort";
    EXPECT_EQ(q.getCapacity(), random)    << "Error: wrong rand queue capacity after bubbleSort";
    EXPECT_EQ(q.size(), 0)                << "Error: wrong rand queue size after bubbleSort";
    EXPECT_EQ(q.indexOf(0), -1)           << "Error: indexOf on empty rand queue after bubbleSort";

    EXPECT_EXIT(q.dequeue(),
    testing::ExitedWithCode(1), "")       << "Error: dequeueing empty rand queue after bubbleSort";
    EXPECT_EXIT(q.peek(),
    testing::ExitedWithCode(1), "")       << "Error: peeking empty rand queue after bubbleSort";

    q.mergeSort();
    EXPECT_EQ(q.isEmpty(), true)          << "Error: wrong rand queue emptiness after mergeSort";
    EXPECT_EQ(q.isFull(), false)          << "Error: wrong rand queue fullness after mergeSort";
    EXPECT_EQ(q.getCapacity(), random)    << "Error: wrong rand queue capacity after mergeSort";
    EXPECT_EQ(q.size(), 0)                << "Error: wrong rand queue size after mergeSort";
    EXPECT_EQ(q.indexOf(0), -1)           << "Error: indexOf on empty rand queue after mergeSort";

    EXPECT_EXIT(q.dequeue(),
    testing::ExitedWithCode(1), "")       << "Error: dequeueing empty rand queue after mergeSort";
    EXPECT_EXIT(q.peek(),
    testing::ExitedWithCode(1), "")       << "Error: peeking empty rand queue after mergeSort";
  }
}

// integration 
TEST_F(QueueTest, SemifullRandomTest) {
  for (int i = 0; i < 1; i++) {
    int random = rand() % 3000 + 1; // get value in range 1-2000
    Queue q = Queue(random);
    int copy[random];
    int val, valBefore;

    for (int i = 0; i < random; i++) {
      copy[i] = i;
    }

    q.enqueue(copy[0]);
    EXPECT_EQ(q.isEmpty(), false)                          << "Error: wrong rand queue emptiness during enqueue";
    EXPECT_EQ(q.isFull(), i != random - 1 ? false : true)  << "Error: wrong rand queue fullness during enqueue";
    EXPECT_EQ(q.getCapacity(), random)                     << "Error: wrong rand queue capacity during enqueue";
    EXPECT_EQ(q.size(), i + 1)                             << "Error: wrong rand queue size during enqueue";
    EXPECT_EQ(q.indexOf(copy[0]), i)                           << "Error: indexOf on empty rand queue during enqueue";

    // fills copy array and queue at the same time
    for (int i = 1; i < random; i++) {
      val = copy[i];
      valBefore = copy[i-1];
      q.enqueue(val);
      EXPECT_EQ(q.isEmpty(), false)                          << "Error: wrong rand queue emptiness during enqueue";
      EXPECT_EQ(q.isFull(), i != random - 1 ? false : true)  << "Error: wrong rand queue fullness during enqueue";
      EXPECT_EQ(q.getCapacity(), random)                     << "Error: wrong rand queue capacity during enqueue";
      EXPECT_EQ(q.size(), i + 1)                             << "Error: wrong rand queue size during enqueue";
      EXPECT_EQ(q.indexOf(val), i)                           << "Error: indexOf on empty rand queue during enqueue";
      EXPECT_EQ(q.indexOf(valBefore), i - 1)                 << "Error: indexOf on empty rand queue during enqueue";
    }
   
    q.clear();
    EXPECT_EQ(q.isEmpty(), true)          << "Error: wrong rand queue emptiness after clear";
    EXPECT_EQ(q.isFull(), false)          << "Error: wrong rand queue fullness after clear";
    EXPECT_EQ(q.getCapacity(), random)    << "Error: wrong rand queue capacity after clear";
    EXPECT_EQ(q.size(), 0)                << "Error: wrong rand queue size after clear";

    EXPECT_EXIT(q.dequeue(),
    testing::ExitedWithCode(1), "")       << "Error: dequeueing empty rand queue after clear";
    EXPECT_EXIT(q.peek(),
    testing::ExitedWithCode(1), "")       << "Error: peeking empty rand queue after clear";
    EXPECT_EQ(q.indexOf(0), -1)           << "Error: indexOf on empty rand queue after clear";
  }
}

// peek
TEST_F(QueueTest, PeekTest) {
  // peek on 0
  Queue zero_q = Queue(0);
  EXPECT_EQ(zero_q.size(), 0) << "Error: expect 0 size";
  EXPECT_EQ(zero_q.getCapacity(), 0) << "Error: expect 0 capacity";

  EXPECT_EXIT(zero_q.peek(),
    testing::ExitedWithCode(1), "") << "Error: peek on zero queue";
  EXPECT_EXIT(zero_q.enqueue(1537),
    testing::ExitedWithCode(1), "") << "Error: enqueue on zero queue";
  EXPECT_EXIT(zero_q.peek(),
    testing::ExitedWithCode(1), "") << "Error: peek on zero queue";
  EXPECT_EXIT(zero_q.dequeue(),
    testing::ExitedWithCode(1), "") << "Error: dequeue on zero queue";
  EXPECT_EXIT(zero_q.peek(),
    testing::ExitedWithCode(1), "") << "Error: peek on zero queue";


  // peek on 1
  Queue single_q = Queue(1);

  EXPECT_EQ(single_q.size(), 0) << "Error: expect 0 size";
  EXPECT_EQ(single_q.getCapacity(), 1) << "Error: expect 1 capacity";

  EXPECT_EXIT(single_q.peek(),
    testing::ExitedWithCode(1), "") << "Error: peek on empty queue";
  single_q.enqueue(65); 
  EXPECT_EQ(single_q.peek(), 65);
  EXPECT_EXIT(single_q.enqueue(153),
  testing::ExitedWithCode(1), "") << "Error: enqueue on max size queue";
  EXPECT_EQ(single_q.peek(), 65);

  single_q.dequeue();
  EXPECT_EXIT(single_q.peek(),
    testing::ExitedWithCode(1), "") << "Error: peak on empty queue";
  
  // peek on many
  int random = rand() % 303 + 1; // get value in range 1-2000
  Queue many_q = Queue(random);
  int copy[random];
  int val;

  for (int i = 0; i < random; i++) {
    val = rand() % 607 + 1;
    copy[i] = val;
    many_q.enqueue(val);
    EXPECT_EQ(many_q.peek(), copy[0]);
  }

  EXPECT_EXIT(many_q.enqueue(931),
  testing::ExitedWithCode(1), "") << "Error: enqueue on full queue";

  for (int i = 0; i < random; i++) {
    EXPECT_EQ(many_q.peek(), copy[i]);
    many_q.dequeue();
  }

  EXPECT_EXIT(single_q.peek(),
  testing::ExitedWithCode(1), "") << "Error: peak on empty queue";

  // peak on default
  Queue default_pq = Queue();
  int d_copy[1000];


  for (int i = 0; i < 1000; i++) {
    val = rand() % 139 + 1;
    d_copy[i] = val;
    default_pq.enqueue(val);
    EXPECT_EQ(default_pq.peek(), d_copy[0]);
  }
  
  EXPECT_EXIT(default_pq.enqueue(104),
  testing::ExitedWithCode(1), "") << "Error: enqueue on full default queue";

  for (int i = 0; i < 1000; i++) {
    EXPECT_EQ(default_pq.peek(), d_copy[i]);
    default_pq.dequeue();
  }

  EXPECT_EXIT(single_q.peek(),
  testing::ExitedWithCode(1), "") << "Error: peak on empty queue";
}

// bubble sort
// TODO add cases of more than just full queues
TEST_F(QueueTest, BubbleSortTest) {

  // [sort on full array]
  int random = rand() % 3000 + 1; // get value in range 1-2000
  Queue full_q = Queue(random);
  int copy[random];
  int val;

  // fill queue, array
  for (int i = 0; i < random; i++) {
    val = rand() % 3000 + 1;
    copy[i] = val;
    full_q.enqueue(val);
  }

  // sort both
  std::sort(copy,copy+random); 
  full_q.bubbleSort();

  for (int i = 0; i < random; i++) {
    EXPECT_EQ(full_q.isEmpty(), false)          << "Error: wrong rand queue emptiness after bubbleSort";
    EXPECT_EQ(full_q.getCapacity(), random)    << "Error: wrong rand queue capacity after bubbleSort";
    EXPECT_EQ(full_q.size(), random - i)                << "Error: wrong rand queue size after bubbleSort";

    int qVal = full_q.dequeue();
    int cVal = copy[i];
    if (qVal != cVal) {
      FAIL() << "incorrect sort order";
    }
  }

  EXPECT_EQ(full_q.isEmpty(), true)          << "Error: wrong rand queue emptiness after bubbleSort";
  EXPECT_EQ(full_q.isFull(), false)          << "Error: wrong rand queue fullness after bubbleSort";
  EXPECT_EQ(full_q.getCapacity(), random)    << "Error: wrong rand queue capacity after bubbleSort";
  EXPECT_EQ(full_q.size(), 0)                << "Error: wrong rand queue size after bubbleSort";
  EXPECT_EQ(full_q.indexOf(0), -1);
}

// merge sort
TEST_F(QueueTest, MergeSortTest) {
  // [sort on full array]
  int random = rand() % 3007 + 1; // get value in range 1-3007
  Queue full_q = Queue(random);
  int copy[random];
  int val;

  // fill queue, array
  for (int i = 0; i < random; i++) {
    val = rand() % 3000 + 1;
    copy[i] = val;
    full_q.enqueue(val);
  }

  // sort both
  std::sort(copy,copy+random); 
  full_q.mergeSort();

  for (int i = 0; i < random; i++) {
    EXPECT_EQ(full_q.isEmpty(), false)          << "Error: wrong rand queue emptiness after mergeSort";
    EXPECT_EQ(full_q.getCapacity(), random)    << "Error: wrong rand queue capacity after mergeSort";
    EXPECT_EQ(full_q.size(), random - i)                << "Error: wrong rand queue size after mergeSort";

    int qVal = full_q.dequeue();
    int cVal = copy[i];
    if (qVal != cVal) {
      FAIL() << "incorrect sort order";
    }
  }

  EXPECT_EXIT(full_q.peek(),
    testing::ExitedWithCode(1), "")          << "Error: peek on zero queue";
  EXPECT_EXIT(full_q.dequeue(),
    testing::ExitedWithCode(1), "")          << "Error: enqueue on zero queue";
  EXPECT_EQ(full_q.isEmpty(), true)          << "Error: wrong rand queue emptiness after mergeSort";
  EXPECT_EQ(full_q.isFull(), false)          << "Error: wrong rand queue fullness after mergeSort";
  EXPECT_EQ(full_q.getCapacity(), random)    << "Error: wrong rand queue capacity after mergeSort";
  EXPECT_EQ(full_q.size(), 0)                << "Error: wrong rand queue size after mergeSort";
  EXPECT_EQ(full_q.indexOf(0), -1);

  // sort on a semi-empty array
  Queue semifull_q = Queue(10);

  for (int i = 0; i < 5; i++) {
    val = rand() % 3000 + 1;
    copy[i] = i;
    semifull_q.enqueue(i);
  }

  std::sort(copy,copy+5); 
  semifull_q.mergeSort();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(semifull_q.isEmpty(), false)                  << "Error: wrong rand queue emptiness after mergeSort";
    EXPECT_EQ(semifull_q.getCapacity(), 10)             << "Error: wrong rand queue capacity after mergeSort";
    EXPECT_EQ(semifull_q.size(), 5 - i)                << "Error: wrong rand queue size after mergeSort";

    int qVal = semifull_q.dequeue();
    int cVal = copy[i];
    if (qVal != cVal) {
      FAIL() << "incorrect sort order";
    }
  }

  EXPECT_EXIT(semifull_q.peek(),
    testing::ExitedWithCode(1), "")          << "Error: peek on zero queue";
  EXPECT_EXIT(semifull_q.dequeue(),
    testing::ExitedWithCode(1), "")          << "Error: enqueue on zero queue";
  EXPECT_EQ(semifull_q.isEmpty(), true)          << "Error: wrong rand queue emptiness after mergeSort";
  EXPECT_EQ(semifull_q.isFull(), false)          << "Error: wrong rand queue fullness after mergeSort";
  EXPECT_EQ(semifull_q.getCapacity(), 10)    << "Error: wrong rand queue capacity after mergeSort";
  EXPECT_EQ(semifull_q.size(), 0)                << "Error: wrong rand queue size after mergeSort";
  EXPECT_EQ(semifull_q.indexOf(0), -1);
}

// clear
// FIXME add default queue on clear test
// FIXME this is clearly not going to cover every case
TEST_F(QueueTest, ClearTest) {
  // random queue
  int random, val, len;
  for (int j = 0; j < 75; j++) {
    random = rand() % 173 + 1;
    Queue clear_q = Queue(random);

    // fill some parts of queue, array
    len = rand() % random + 1;
    for (int i = 0; i < len; i++) {
      val = rand() % 3000 + 1;
      clear_q.enqueue(val);
      EXPECT_EQ(clear_q.getCapacity(), random);
      EXPECT_EQ(clear_q.size(), i + 1);
    }
    
    clear_q.clear();
  
    EXPECT_EXIT(clear_q.peek(),
      testing::ExitedWithCode(1), "")          << "Error: peek on empty queue";
    EXPECT_EXIT(clear_q.dequeue(),
      testing::ExitedWithCode(1), "")          << "Error: enqueue on empty queue";
    EXPECT_EQ(clear_q.isEmpty(), true)          << "Error: wrong rand queue emptiness after mergeSort";
    EXPECT_EQ(clear_q.isFull(), false)          << "Error: wrong rand queue fullness after mergeSort";
    EXPECT_EQ(clear_q.getCapacity(), random)    << "Error: wrong rand queue capacity after mergeSort";
    EXPECT_EQ(clear_q.size(), 0)                << "Error: wrong rand queue size after mergeSort";
    EXPECT_EQ(clear_q.indexOf(0), -1);
  }
}

// indexOf
TEST_F(QueueTest, IndexOfTest) {
  int random, val, len;
  random = rand() % 157 + 1;
  Queue index_q = Queue(random);
  int index_copy[random];

  // fill some parts of queue, array
  len = rand() % random + 1;
  for (int i = 0; i < len; i++) {
    val = rand() % 157 + 1;
    index_copy[i] = val;
    index_q.enqueue(val);
    EXPECT_EQ(index_q.getCapacity(), random);
    EXPECT_EQ(index_q.size(), i + 1);
  }

  // check for random numbers
  for (int i = 0; i < len; i++) {
    val = rand() % 157 + 1;
    int qIndex = index_q.indexOf(val);
    int cIndex = -1;
    // searches for val in copy array
    for (int j = 0; j < len; j++) {
      if (index_copy[j] == val) {
        cIndex = j;
        break;
      }
    }
    EXPECT_EQ(cIndex, qIndex) << "indexOf not working properly";
  }
}

// memory, sort of
// FIXME add more cases esp overflow/underflow shenanigans
TEST_F(QueueTest, SizeTest) {
  Queue size_q = Queue();
  int byteSize = sizeof(size_q);
  EXPECT_EQ(byteSize, 24) << "Error: wrong byte size";
  // 24 because ptr (8 bytes) + 4 int * (4 bytes) = 24
}

// constructor
// FIXME fix redundancy via loop
TEST_F(QueueTest, ConstructorTest) {
  int random;
  EXPECT_THROW(Queue(-153), std::bad_array_new_length)  << "Error: negative size init for queue permitted";

  Queue default_constructor_q = Queue();
  EXPECT_EQ(default_constructor_q.size(), 0);
  EXPECT_EQ(default_constructor_q.getCapacity(), 1000);
  EXPECT_EQ(default_constructor_q.indexOf(0), -1);
  EXPECT_EQ(default_constructor_q.indexOf(1000), -1);
  EXPECT_EQ(default_constructor_q.indexOf(15.3), -1);

  for (int j = 0; j < 153; j++) {
    random = rand() % 413 + 1;
    Queue constructor_q = Queue(random);
    EXPECT_EXIT(constructor_q.dequeue(),
        testing::ExitedWithCode(1), "");
    EXPECT_EXIT(constructor_q.peek(),
        testing::ExitedWithCode(1), "");
    EXPECT_EQ(constructor_q.size(), 0);
    EXPECT_EQ(constructor_q.getCapacity(), random);
    EXPECT_EQ(constructor_q.indexOf(0), -1);
    EXPECT_EQ(constructor_q.indexOf(1000), -1);
    EXPECT_EQ(constructor_q.indexOf(15.3), -1);
  }
}

// dequeue
TEST_F(QueueTest, DequeueTest) {
  for (int j = 0; j < 15; j++) {
    int random, val, len;
    int qVal, cVal;
    std::string output;
    random = rand() % 413 + 1;
    Queue dequeue_q = Queue(random);
    int dequeue_copy[random];

    EXPECT_EXIT(dequeue_q.dequeue(),
        testing::ExitedWithCode(1), "");

    // fill queue randomly, copy array
    len = rand() % random + 1;
    for (int i = 0; i < len; i++) {
      val = rand() % 251 + 1;
      dequeue_copy[i] = val;
      dequeue_q.enqueue(val);
      EXPECT_EQ(dequeue_q.getCapacity(), random);
      EXPECT_EQ(dequeue_q.size(), i + 1);
    }

    for (int i = 0; i < len; i++) {
      testing::internal::CaptureStdout();
      qVal = dequeue_q.dequeue();
      output = testing::internal::GetCapturedStdout();
      cVal = dequeue_copy[i];
      EXPECT_EQ(output, "Removing " + std::to_string(cVal) + "\n");
      EXPECT_EQ(qVal, dequeue_copy[i]);
    }

    EXPECT_EXIT(dequeue_q.dequeue(),
      testing::ExitedWithCode(1), "");
  }
}