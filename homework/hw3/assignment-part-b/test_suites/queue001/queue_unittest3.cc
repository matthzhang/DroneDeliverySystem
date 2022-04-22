#include "gtest/gtest.h"
#include "queue.h"

class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
    q1 = new Queue(5);
    q1->enqueue(1);
    q1->enqueue(2);
    q1->enqueue(3);

    q2 = new Queue();

    q4 = new Queue(7);
    q4->enqueue(10);
    q4->enqueue(74);
    q4->enqueue(7);
    q4->enqueue(18);
    q4->enqueue(101);
    q4->enqueue(53);
    q4->enqueue(4);
  }
  void TearDown() {
    // code here will execute just after the test ends
    delete q1;
    delete q2;
    delete q4;
  }
 protected:
  Queue* q1;
  Queue* q2;
  Queue* q4;
};

TEST_F(QueueTest, QueueConstrutorTest) {
  EXPECT_EQ(q1->getCapacity(), 5) << "capacity not set correctly";
  EXPECT_EQ(q1->peek(), 1) << "front not setup correctly";
  EXPECT_EQ(q1->size(), 3) << "size not updated correctly";
  EXPECT_EQ(sizeof(*q1), 24) << "queue is taking up wrong amount of space";

  EXPECT_EQ(q2->getCapacity(), 1000) << "capacity not set correctly";
  EXPECT_EQ(q2->size(), 0) << "size not setup correctly";
  EXPECT_EQ(sizeof(*q2), 24) << "queue is taking up wrong amount of space";
}

TEST_F(QueueTest, QueueDestructorTest) {
  Queue* q3 = new Queue(3);
  q3->enqueue(1);
  delete q3;
  EXPECT_EXIT(q3->peek(), testing::KilledBySignal(SIGSEGV),".*") << "destructor did not work properly";
}

TEST_F(QueueTest, DequeueTest) {
  EXPECT_EQ(q1->dequeue(), 1) << "dequeue not working correctly in normal case";
  EXPECT_EQ(q1->size(), 2) << "size not updated properly after dequeue";
  EXPECT_EQ(q1->peek(), 2) << "front not updated properly after dequeue";
  EXPECT_EQ(q1->indexOf(2), 0) << "front not updated correctly after dequeue";
  EXPECT_EQ(q1->indexOf(3), 1) << "second element not correct after dequeue";

  q1->dequeue();
  q1->dequeue();
  EXPECT_EXIT(q1->dequeue(),testing::ExitedWithCode(EXIT_FAILURE), "") << "dequeuing from an empty queue did not exit";

  q1->enqueue(1);
  testing::internal::CaptureStdout();
  q1->dequeue();
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Removing 1\n") << "dequeue did not print the correct value";
}

TEST_F(QueueTest, EnqueueTest) {
  q1->enqueue(4);

  EXPECT_EQ(q1->size(), 4) << "size not updated properly after enqueue";
  EXPECT_EQ(q1->indexOf(4), 3) << "rear not updated properly after enqueue";

  testing::internal::CaptureStdout();
  q1->enqueue(3);
  string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "Inserting 3\n") << "enqueue did not print the correct value";

  EXPECT_EXIT(q1->enqueue(2),testing::ExitedWithCode(EXIT_FAILURE), "") << "enqueuing to a full queue did not exit";
}

TEST_F(QueueTest, PeekTest) {
  EXPECT_EQ(q1->peek(), 1) << "peek not working correctly in normal case";
  EXPECT_EQ(q1->size(), 3) << "size not correct after peek";
  q1->enqueue(4);
  q1->enqueue(5);
  EXPECT_EQ(q1->peek(), 1) << "peek not working correctly in full queue case";

  q1->dequeue();
  EXPECT_EQ(q1->peek(), 2) << "peek not working correctly after dequeue";
  q1->clear();
  q1->enqueue(1);
  EXPECT_EQ(q1->peek(), 1) << "peek not working correctly in one element in queue case";
  q1->dequeue();
  EXPECT_EXIT(q1->peek(),testing::ExitedWithCode(EXIT_FAILURE), "") << "peeking a empty queue did not exit";

  EXPECT_EXIT(q2->peek(),testing::ExitedWithCode(EXIT_FAILURE), "") << "peeking from an empty, just intialized queue, did not eixt";

  for(int i = 1; i < 100; i++){
    Queue* q5 = new Queue(i);
    for(int j = 0; j < i; j++){
      q5->enqueue(j);
    }
    for(int j = 0; j < i; j++){
      EXPECT_EQ(q5->peek(), j) << "peeking from a queue of size " << i << " did not work correctly";
      q5->dequeue();
    }
    delete q5;
  }
}

TEST_F(QueueTest, IndexOfTest) {
  EXPECT_EQ(q1->indexOf(1), 0) << "indexOf not working correctly in normal case";
  EXPECT_EQ(q1->indexOf(2), 1) << "indexOf not working correctly in normal case";
  EXPECT_EQ(q1->indexOf(3), 2) << "indexOf not working correctly in normal case";
  EXPECT_EQ(q1->indexOf(4), -1) << "indexOf not working correctly in case where element is not in the queue";
}

TEST_F(QueueTest, SizeTest) {
  EXPECT_EQ(q1->size(), 3) << "size not working correctly in normal case";
  q1->dequeue();
  EXPECT_EQ(q1->size(), 2) << "size not working correctly after dequeue";
  q1->enqueue(4);
  EXPECT_EQ(q1->size(), 3) << "size not working correctly after enqueue";

  q1->enqueue(5);
  q1->enqueue(6);
  EXPECT_EQ(q1->size(), 5) << "size not working correctly for full queue";
  q1->peek();
  EXPECT_EQ(q1->size(), 5) << "size not working correctly after peek";
  q1->clear();
  EXPECT_EQ(q1->size(), 0) << "size not working correctly after queue has been cleared";

  EXPECT_EQ(q2->size(), 0) << "size not working correctly in empty queue case";
}

TEST_F(QueueTest, IsEmptyTest) {
  EXPECT_EQ(q1->isEmpty(), false) << "isEmpty not working correctly in normal case";
  q1->dequeue();
  q1->dequeue();
  q1->dequeue();
  EXPECT_EQ(q1->isEmpty(), true) << "isEmpty not working correctly after queue has been emptied by dequeues";
  q1->enqueue(4);
  EXPECT_EQ(q1->isEmpty(), false) << "isEmpty not working correctly after enqueue to an empty queue";
  q1->enqueue(5);
  q1->clear();
  EXPECT_EQ(q1->isEmpty(), true) << "isEmpty not working correctly after queue has been cleared";

  EXPECT_EQ(q2->isEmpty(), true) << "isEmpty not working correctly for a queue that has just been intialized";
}

TEST_F(QueueTest, IsFullTest) {
  EXPECT_EQ(q1->isFull(), false) << "isFull not working correctly in normal case";
  q1->enqueue(4);
  q1->enqueue(5);
  EXPECT_EQ(q1->isFull(), true) << "isFull not working correctly after queue has been filled by enqueues";
  q1->dequeue();
  EXPECT_EQ(q1->isFull(), false) << "isFull not working correctly after dequeue from a full queue";
  q1->enqueue(5);
  q1->clear();
  EXPECT_EQ(q1->isFull(), false) << "isFull not working correctly after queue has been cleared";

  EXPECT_EQ(q2->isFull(), false) << "isFull not working correctly for a queue that has just been intialized";
}

TEST_F(QueueTest, GetCapacityTest) {
  EXPECT_EQ(q1->getCapacity(), 5) << "getCapacity not working correctly in normal case";
  q1->enqueue(4);
  q1->enqueue(5);
  EXPECT_EQ(q1->getCapacity(), 5) << "getCapacity not working correctly after queue has been filled by enqueues";
  q1->dequeue();
  EXPECT_EQ(q1->getCapacity(), 5) << "getCapacity not working correctly after dequeue from a full queue";
  q1->enqueue(5);
  q1->clear();
  EXPECT_EQ(q1->getCapacity(), 5) << "getCapacity not working correctly after queue has been cleared";

  EXPECT_EQ(q2->getCapacity(), 1000) << "getCapcity not working correctly for a queue that has just been intialized with defalut capacity";
}

TEST_F(QueueTest, ClearTest) {
  q1->clear();
  EXPECT_EQ(q1->size(), 0) << "size not working correctly after queue has been cleared";
  EXPECT_EQ(q1->getCapacity(), 5) << "getCapacity not working correctly after queue has been cleared";
  EXPECT_EQ(q1->indexOf(1), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q1->indexOf(2), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q1->indexOf(3), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EXIT(q1->dequeue(),testing::ExitedWithCode(EXIT_FAILURE), "") << "dequeing from a queue that was just cleared did not exit";

  q1->enqueue(1);
  q1->enqueue(2);
  q1->dequeue();
  q1->clear();
  EXPECT_EXIT(q1->peek(),testing::ExitedWithCode(EXIT_FAILURE), "") << "peeking from a queue that was just cleared did not result in exit";

  q4->clear();
  EXPECT_EQ(q4->size(), 0) << "size not working correctly after queue has been cleared";
  EXPECT_EQ(q4->getCapacity(), 7) << "getCapacity not working correctly after queue has been cleared";
  EXPECT_EQ(q4->indexOf(4), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q4->indexOf(7), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q4->indexOf(10), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q4->indexOf(18), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q4->indexOf(53), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q4->indexOf(74), -1) << "indexOf showing clear did not work correctly";
  EXPECT_EQ(q4->indexOf(101), -1) << "indexOf showing clear did not work correctly";
}

TEST_F(QueueTest, BubbleSortTest) {
  q1->enqueue(10);
  q1->enqueue(7);

  q1->bubbleSort();
  EXPECT_EQ(q1->indexOf(1), 0) << "bubbleSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(2), 1) << "bubbleSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(3), 2) << "bubbleSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(7), 3) << "bubbleSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(10), 4) << "bubbleSort did not sort the 5 element queue correctly";

  q4->bubbleSort();
  EXPECT_EQ(q4->indexOf(4), 0) << "bubbleSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(7), 1) << "bubbleSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(10), 2) << "bubbleSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(18), 3) << "bubbleSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(53), 4) << "bubbleSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(74), 5) << "bubbleSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(101), 6) << "bubbleSort did not sort the 7 element queue correctly";
}

TEST_F(QueueTest, MergeSortTest) {
  q1->enqueue(10);
  q1->enqueue(7);

  q1->mergeSort();
  EXPECT_EQ(q1->indexOf(1), 0) << "mergeSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(2), 1) << "mergeSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(3), 2) << "mergeSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(7), 3) << "mergeSort did not sort the 5 element queue correctly";
  EXPECT_EQ(q1->indexOf(10), 4) << "mergeSort did not sort the 5 element queue correctly";

  q4->mergeSort();
  EXPECT_EQ(q4->indexOf(4), 0) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(7), 1) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(10), 2) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(18), 3) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(53), 4) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(74), 5) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->indexOf(101), 6) << "mergeSort did not sort the 7 element queue correctly";
  EXPECT_EQ(q4->getCapacity(), 7) << "capacity not correct after mergeSort";
  EXPECT_EQ(q4->peek(), 4) << "seek not correct after mergeSort";
  EXPECT_EQ(q4->size(), 7) << "size not correct after mergeSort";
  EXPECT_EQ(sizeof(*q4), 24) << "queue is taking up wrong amount of space after mergeSort";
  

  for(int i = 0; i < 100; i++){
    Queue* q5 = new Queue(i);
    for(int j = 0; j < i; j++){
      q5->enqueue(q5->getCapacity() - j - 1);
    }
    q5->mergeSort();
    for(int j = 0; j < i; j++){
      EXPECT_EQ(q5->peek(), j) << "mergeSort did not sort a " << i << " element queue correctly";
      q5->dequeue();
    }
    delete q5;
  }
}
