#include "gtest/gtest.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
  }
  void TearDown() {
    // code here will execute just after the test ends
  }
 protected:
};

/**************************************************************
***************************************************************
enqueue() and dequeue()
***************************************************************
**************************************************************/

TEST_F(QueueTest, AttemptToEnqueueToQueueWithZeroCapacity) {
  Queue zero = Queue(0);
  EXPECT_EXIT(zero.enqueue(1), testing::ExitedWithCode(1), "") << "Incorrectly handles enqueueing to a zero capacity queue";
}

TEST_F(QueueTest, AttemptToEnqueuePastCapacity) {
  Queue cap = Queue(2);
  cap.enqueue(1);
  cap.enqueue(2);
  EXPECT_EXIT(cap.enqueue(3), testing::ExitedWithCode(1), "");
}

TEST_F(QueueTest, EnqueueingInCorrectOrder1) {
  Queue order1 = Queue(10);
  for (int i = 0; i < 10; i++) {
    order1.enqueue(i);
  } 
  for (int i = 0; i < 10; i++) {
    if (order1.dequeue() != i) {
      FAIL();
    }
  }
}

TEST_F(QueueTest, EnqueueingInCorrectOrder2) {
  Queue order2 = Queue(100);
  for (int i = 0; i < 100; i++) {
    order2.enqueue(i);
  } 
  for (int i = 0; i < 100; i++) {
    if (order2.dequeue() != i) {
      FAIL();
    }
  }
}

TEST_F(QueueTest, EnqueueingThenDequeueingThenEnqueueingAgainKeepsOrder) {
  Queue order4 = Queue(1000);
  int i;
  for (i = 0; i < 500; i++) {
    order4.enqueue(i);
  }
  for (i = 0; i < 50; i++) {
    order4.dequeue();
  }
  for (i = 500; i < 1000; i++) {
    order4.enqueue(i);
  }
  for (i = 50; i < 1000; i++) {
    if (order4.dequeue() != i) {
      FAIL();
    }
  }
}

TEST_F(QueueTest, CheckPrintEnqueueCorrectly) {
  Queue shit = Queue(10);
  for (int j = 0; j < 10; j++) {
    testing::internal::CaptureStdout();
    shit.enqueue(j);
    std::string output = testing::internal::GetCapturedStdout();

    std::string num = std::to_string(j);
    std::string actual = "Inserting " + num + "\n";
    EXPECT_EQ(output, actual);
  }
}

TEST_F(QueueTest, CheckPrintDequeueCorrectly) {
  Queue shit = Queue(10);
  for (int j = 0; j < 10; j++) {
    shit.enqueue(j);
  }
  for (int j = 0; j < 10; j++) {
    testing::internal::CaptureStdout();
    int deq = shit.dequeue();
    std::string output = testing::internal::GetCapturedStdout();

    std::string num = std::to_string(j);
    std::string actual = "Removing " + num + "\n";
    EXPECT_EQ(output, actual);
    EXPECT_EQ(deq, j);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Peek tests
////////////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, PeekingWithOneElement) {
  Queue q1 = Queue();
  q1.enqueue(100);
  EXPECT_EQ(q1.peek(), 100) << "peek peaks at wrong element when single element in queue";
}

TEST_F(QueueTest, PeekingWithTwoElements) {
  Queue q2 = Queue();
  q2.enqueue(1);
  q2.enqueue(2);
  EXPECT_EQ(q2.peek(), 1) << "peek peeks at wrong element when two elements in queue";
}

TEST_F(QueueTest, PeekingWhenQueueIsFull) {
  Queue q3 = Queue(4);
  for (int i = 0; i < 4; i++) {
    q3.enqueue(i);
  }
  EXPECT_EQ(q3.peek(), 0) << "fails to peek when queue is full";
}

TEST_F(QueueTest, PeekingWhenQueueHasZeroCapacity) {
  Queue q5 = Queue(0);
  EXPECT_EXIT(q5.peek(), testing::ExitedWithCode(1), "") << "fails to handle peek when zero capacity queue";
}

TEST_F(QueueTest, PeekingAtElementWhereElementOneAndTwoAreSame) {
  Queue q10 = Queue(2);
  q10.enqueue(1);
  q10.enqueue(1);
  EXPECT_EQ(q10.peek(), 1) << "Failed to peek when the next number is the same";
}

TEST_F(QueueTest, DequeueElementZeroThenPeekOneElementQueue) {
  Queue q12 = Queue(1);
  q12.enqueue(10);
  q12.dequeue();
  EXPECT_EXIT(q12.peek(), testing::ExitedWithCode(1), "") << "Failed to exit properly when peeking just after dequeueing into an empty queue";
}

//////////////////////////////////////////////////////////////////////////////
// indexOf() tests -- CANNOT INDEXOF LESS THAN TWO ELEMENTS
//////////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, IndexOfFirstElementInQueueWithTwoElementsAndFull) {
  Queue q1 = Queue(3);
  q1.enqueue(100);
  q1.enqueue(200);
  q1.enqueue(300);
  EXPECT_EQ(q1.indexOf(100), 0) << "indexOf failed to get first element index";
}

TEST_F(QueueTest, IndexOfLastElementInQueueWithTwoElementsAndFull) {
  Queue q1 = Queue(3);
  q1.enqueue(100);
  q1.enqueue(200);
  q1.enqueue(300);
  EXPECT_EQ(q1.indexOf(300), 2) << "indexOf fialed to get last element index";
}

TEST_F(QueueTest, IndexOfElementJustDeletedOutOfFiveElementFullQueue) {
  Queue q2 = Queue(5);
  q2.enqueue(100);
  q2.enqueue(200);
  q2.enqueue(300);
  q2.enqueue(400);
  q2.enqueue(500);
  q2.dequeue();
  EXPECT_EQ(q2.indexOf(100), -1) << "indexOf failed to get nonexistent element index";
}


TEST_F(QueueTest, IndexOfElementThatDoesNotAndHasNeverExistedInQueue) {
  Queue q3 = Queue(3);
  q3.enqueue(1);
  q3.enqueue(2);
  q3.enqueue(3);
  EXPECT_EQ(q3.indexOf(8000), -1) << "indexOf failed to get nonexistent element index";
}

TEST_F(QueueTest, IndexOfElementInMiddleOfLargeQueue) {
  Queue q6 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q6.enqueue(i);
  }
  EXPECT_EQ(q6.indexOf(50), 50) << "indexOf failed to get index in middle of queue";
}

// //////////////////////////////////////////////////////////////////////////
// // size() tests
// //////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, SizeOfFullOneElementCapacityQueue) {
  Queue q1 = Queue(1);
  q1.enqueue(1);
  EXPECT_EQ(q1.size(), 1) << "size of 1 element queue not correct";
}

TEST_F(QueueTest, SizeOfQueueAfterMultipleEnqueuesAndDequeues) {
  Queue q4 = Queue(5);
  q4.enqueue(100);
  q4.enqueue(200);
  q4.enqueue(300);
  q4.dequeue();
  q4.dequeue();
  q4.dequeue();
  EXPECT_EQ(q4.size(), 0) << "size of empty queue not correct";
}

TEST_F(QueueTest, SizeOfLargeFullQueue) {
  Queue q6 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q6.enqueue(i*2);
  }
  EXPECT_EQ(q6.size(), 100) << "size of full queue incorrect";
}

// //////////////////////////////////////////////////////////////////////////
// // isEmpty() tests
// //////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, QueueWithZeroCapacityIsEmpty) {
  Queue q1 = Queue(0);
  EXPECT_TRUE(q1.isEmpty()) << "failed to say 0 queue is empty";
}

TEST_F(QueueTest, LargeFullQueueIsNotEmpty) {
  Queue q5 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q5.enqueue(i);
  }
  EXPECT_FALSE(q5.isEmpty()) << "failed to say full queue is not empty";
}

TEST_F(QueueTest, LargeFullQueueThenDequeuedUntilEmptyIsEmpty) {
  Queue q6 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q6.enqueue(i);
  }
  for (int i = 0; i < 100; i++) {
    q6.dequeue();
  }
  EXPECT_TRUE(q6.isEmpty()) << "failed to say empty queue is empty";
}

TEST_F(QueueTest, QueueFullThenDequeuedUntilOneElementIsNotEmpty) {
  Queue q7 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q7.enqueue(i);
  }

  for (int i = 0; i < 100-1; i++) {
    q7.dequeue();
  }
  EXPECT_FALSE(q7.isEmpty()) << "failed to confirm not empty queue is not empty";
}

// //////////////////////////////////////////////////////////////////////////
// // isFull() tests
// //////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, QueueWithZeroCapacityIsFull) {
  Queue q1 = Queue(0);
  EXPECT_TRUE(q1.isFull()) << "failed to say zero capacity queue is full";
}

TEST_F(QueueTest, QueueWithTwoCapacityAndOneElementIsNotFull) {
  Queue q5 = Queue(2);
  q5.enqueue(1);
  EXPECT_FALSE(q5.isFull()) << "failed to say half full queue is not full";
}

TEST_F(QueueTest, QueueWithTwoCapacityAndTwoElementsIsFull) {
  Queue q6 = Queue(2);
  q6.enqueue(1);
  q6.enqueue(2);
  EXPECT_TRUE(q6.isFull()) << "failed to say full queue is full";
}

TEST_F(QueueTest, BiggerQueueAlmostFullIsNotFull) {
  Queue q7 = Queue(100);
  for (int i = 0; i < 99; i++) {
    q7.enqueue(i);
  }
  EXPECT_FALSE(q7.isFull()) << "failed to say not full queue is not full";
}

TEST_F(QueueTest, BigQueueWithFullElementsIsFull) {
  Queue q8 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q8.enqueue(i);
  }
  EXPECT_TRUE(q8.isFull()) << "failed to say full queue is full";
}

TEST_F(QueueTest, FullQueueThenDequeueIsNotFull) {
  Queue q9 = Queue(100);
  for (int i = 0; i < 100; i++) {
    q9.enqueue(i);
  }
  q9.dequeue();
  EXPECT_FALSE(q9.isFull()) << "failed to say almost full queue is not full";
}

// //////////////////////////////////////////////////////////////////////////
// // clear() tests
// //////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, AttemptToClearOneElementFullQueue) {
  Queue c1 = Queue(1);
  c1.enqueue(1);
  c1.clear();

  EXPECT_TRUE(c1.isEmpty()) << "queue is not empty after clear";
  EXPECT_EQ(c1.getCapacity(), 1) << "capacity changes after clear";
  EXPECT_EQ(c1.size(), 0) << "size is not 0 after clear";
}

TEST_F(QueueTest, AttemptToClearLargeNotFullQueue) {
  Queue c3 = Queue(100);
  for (int i = 0; i < 75; i++) {
    c3.enqueue(i);
  }

  c3.clear();

  EXPECT_TRUE(c3.isEmpty()) << "queue is not empty after clear";
  EXPECT_EQ(c3.getCapacity(), 100) << "capacity changes after clear";
  EXPECT_EQ(c3.size(), 0) << "size is not zero after clear";
}

TEST_F(QueueTest, AttemptToClearLargeFullQueue) {
  Queue c3 = Queue(1000);
  for (int i = 0; i < 1000; i++) {
    c3.enqueue(i);
  }

  c3.clear();

  EXPECT_TRUE(c3.isEmpty()) << "queue is not empty after clear";
  EXPECT_EQ(c3.getCapacity(), 1000) << "capacity changes after clear";
  EXPECT_EQ(c3.size(), 0) << "size changes after clear";
}

// //////////////////////////////////////////////////////////////////////////
// // bubbleSort() tests
// //////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, AttemptToBubbleSortSortedNotFullQueue) {
  Queue b3 = Queue(5);
  b3.enqueue(1);
  b3.enqueue(2);
  b3.enqueue(3);
  b3.bubbleSort();
  for (int i = 0; i < b3.size(); i++) {
    if (b3.dequeue() > b3.peek()) {
      FAIL() << "bubble sort failed to sort";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedNotFullQueue2) {
  Queue b3 = Queue(5);
  b3.enqueue(1);
  b3.enqueue(2);
  b3.enqueue(3);
  b3.bubbleSort();
  for (int i = 0; i < b3.size(); i++) {
    EXPECT_EQ(b3.dequeue(), i+1);
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedFullQueue) {
  Queue b3 = Queue(5);
  b3.enqueue(1);
  b3.enqueue(2);
  b3.enqueue(3);
  b3.enqueue(4);
  b3.enqueue(5);
  b3.bubbleSort();
  for (int i = 0; i < b3.size(); i++) {
    if (b3.dequeue() > b3.peek()) {
      FAIL() << "bubble sort failed to sort";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedFullQueue2) {
  Queue b3 = Queue(5);
  b3.enqueue(1);
  b3.enqueue(2);
  b3.enqueue(3);
  b3.enqueue(4);
  b3.enqueue(5);
  b3.bubbleSort();
  for (int i = 0; i < b3.size(); i++) {
    EXPECT_EQ(b3.dequeue(), i+1);
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedNotFullLargeQueue) {
  Queue b4 = Queue(100);
  for (int i = 0; i < 75; i++) {
    b4.enqueue(i);
  }
  b4.bubbleSort();
  for (int i = 0; i < b4.size(); i++) {
    if (b4.dequeue() > b4.peek()) {
      FAIL() << "bubble sort failed to sort";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedNotFullLargeQueue2) {
  Queue b4 = Queue(100);
  for (int i = 0; i < 75; i++) {
    b4.enqueue(i);
  }
  b4.bubbleSort();
  for (int i = 0; i < b4.size(); i++) {
    EXPECT_EQ(b4.dequeue(), i);
  }
}

TEST_F(QueueTest, AttemptToBubbleSortNotSortedNotFullLargeQueue) {
  Queue b4 = Queue(100);
  for (int i = 74; i >= 0; i--) {
    b4.enqueue(i);
  }
  b4.bubbleSort();
  for (int i = 0; i < b4.size(); i++) {
    if (b4.dequeue() > b4.peek()) {
      FAIL() << "bubble sort failed to sort";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortNotSortedNotFullLargeQueue2) {
  Queue b4 = Queue(100);
  for (int i = 74; i >= 0; i--) {
    b4.enqueue(i);
  }
  b4.bubbleSort();
  for (int i = 0; i < b4.size(); i++) {
    EXPECT_EQ(b4.dequeue(), i);
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedFullLargeQueue) {
  Queue b4 = Queue(100);
  for (int i = 0; i < 100; i++) {
    b4.enqueue(i);
  }
  b4.bubbleSort();
  for (int i = 0; i < b4.size(); i++) {
    if (b4.dequeue() > b4.peek()) {
      FAIL() << "bubble sort failed to sort";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortSortedFullLargeQueue2) {
  Queue b4 = Queue(100);
  for (int i = 0; i < 100; i++) {
    b4.enqueue(i);
  }
  b4.bubbleSort();
  for (int i = 0; i < b4.size(); i++) {
    EXPECT_EQ(b4.dequeue(), i);
  }
}

TEST_F(QueueTest, AttemptToBubbleSortNotSortedFullLargeQueue) {
  Queue b5 = Queue(100);
  for (int i = 99; i >= 0; i--) {
    b5.enqueue(i);
  }
  b5.bubbleSort();
  for (int i = 0; i < b5.size(); i++) {
    if (b5.dequeue() > b5.peek()) {
      FAIL() << "bubble sort failed to sort";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortNotSortedFullLargeQueue2) {
  Queue b5 = Queue(100);
  for (int i = 99; i >= 0; i--) {
    b5.enqueue(i);
  }
  b5.bubbleSort();
  for (int i = 0; i < b5.size(); i++) {
    EXPECT_EQ(b5.dequeue(), i);
  }
}

TEST_F(QueueTest, AttemptToBubbleSortAllSameElement) {
  Queue b6 = Queue(100);
  for (int i = 0; i < 100; i++) {
    b6.enqueue(1);
  }
  b6.bubbleSort();
  for (int i = 0; i < 100; i++) {
    if (b6.dequeue() != 1) {
      FAIL() << "bubble sort introduced a new number to the queue somehow";
    }
  }
}

TEST_F(QueueTest, AttemptToBubbleSortAllSameElement2) {
  Queue b6 = Queue(100);
  for (int i = 0; i < 100; i++) {
    b6.enqueue(1);
  }
  b6.bubbleSort();
  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(b6.dequeue(), 1);
  }
}


// //////////////////////////////////////////////////////////////////////////
// // mergeSort() tests
// //////////////////////////////////////////////////////////////////////////


TEST_F(QueueTest, AttemptToMergeSortSortedNotFullLargeQueue) {
  Queue b4 = Queue(100);
  for (int i = 0; i < 75; i++) {
    b4.enqueue(i);
  }
  b4.mergeSort();
  for (int i = 0; i < b4.size(); i++) {
    if (b4.dequeue() != i) {
      FAIL() << "merge sort failed to sort correctly";
    }
  }
}

TEST_F(QueueTest, AttemptToMergeSortSortedNotFullLargeQueue2) {
  Queue b4 = Queue(100);
  for (int i = 0; i < 75; i++) {
    b4.enqueue(i);
  }
  b4.mergeSort();
  for (int i = 0; i < b4.size(); i++) {
    EXPECT_EQ(b4.dequeue(), i);
  }
}

TEST_F(QueueTest, AttemptToMergeSortNotSortedNotFullLargeQueue) {
  Queue b4 = Queue(100);
  for (int i = 74; i >= 0; i--) {
    b4.enqueue(i);
  }
  b4.mergeSort();
  for (int i = 0; i < b4.size(); i++) {
    if (b4.dequeue() != i) {
      FAIL() << "merge sort failed to sort correctly";
    }
  }
}

TEST_F(QueueTest, AttemptToMergeSortNotSortedNotFullLargeQueue2) {
  Queue b4 = Queue(100);
  for (int i = 74; i >= 0; i--) {
    b4.enqueue(i);
  }
  b4.mergeSort();
  for (int i = 0; i < b4.size(); i++) {
    EXPECT_EQ(b4.dequeue(), i);
  }
}

TEST_F(QueueTest, Merge) {
    Queue un = Queue(100);
    for (int i = 0; i < 100; i++) {
        un.enqueue(i-25);
    }
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(un.dequeue(), i-25) << "merge sort failed to sort correctly";
    }
}

TEST_F(QueueTest, MergeSortAllSameButOne) {
  Queue merg = Queue(100); 
  merg.enqueue(3);
  for (int i = 0; i < 99; i++) {
    merg.enqueue(2);
  }
  merg.mergeSort();
  for (int i = 0; i < 99; i++) {
    EXPECT_EQ(merg.dequeue(), 2);
  }
  EXPECT_EQ(merg.dequeue(), 3);
}


// //////////////////////////////////////////////////////////////////////////
// // misc tests
// //////////////////////////////////////////////////////////////////////////

TEST_F(QueueTest, SpaceTest) {
  Queue sp = Queue(10);
  sp.enqueue(100);
  sp.enqueue(10);
  sp.dequeue();
  sp.enqueue(43);
  EXPECT_EQ(sizeof(sp), 24) << "queue is larger than it should be in bytes";
}


