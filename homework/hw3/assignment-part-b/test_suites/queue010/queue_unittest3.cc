#include "gtest/gtest.h"
#include "queue.h"

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

TEST_F(QueueTest, AddingOrder) {
  Queue q1(4);
  q1.enqueue(10);
  q1.enqueue(11);
  EXPECT_EQ(q1.indexOf(10),0) << "IndexOf not working";
  EXPECT_EQ(q1.indexOf(11),1) << "IndexOf not working";
  EXPECT_EQ(q1.isFull(),false) << "isFull not working";
}

TEST_F(QueueTest, Clearing) {
  Queue q1(4);
  q1.enqueue(1);
  q1.enqueue(2);
  q1.enqueue(3);  
  q1.enqueue(4);
  EXPECT_EQ(q1.isFull(), true) << "isFull not ordering properly";
  q1.clear();
  EXPECT_EQ(q1.isEmpty(), true) << "Enqueue not ordering properly";
  EXPECT_EQ(q1.isFull(), false) << "clear() or isFull not ordering properly";
  EXPECT_EXIT(q1.dequeue(),testing::ExitedWithCode(1),"") << "clear() not ordering properly";
}

TEST_F(QueueTest, Clearing2) {
  Queue q1(3);
  q1.enqueue(1);
  q1.enqueue(2);
  q1.enqueue(3);
  q1.dequeue();
  q1.enqueue(4);
  testing::internal::CaptureStdout();
  q1.clear();
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "Removing 2\nRemoving 3\nRemoving 4\n") << "dequeue not printing properly";
}


TEST_F(QueueTest, Bytes) {
  Queue q1(2);
  EXPECT_EQ(sizeof(q1),24) << "Taking up wrong amount of space";
  q1.enqueue(4);
  EXPECT_EQ(sizeof(q1),24) << "Taking up wrong amount of space";
}

TEST_F(QueueTest, Dequeue) {
  Queue q1(4);
  q1.enqueue(1);
  q1.enqueue(2);
  q1.enqueue(3);  
  q1.enqueue(4);
  EXPECT_EQ(q1.dequeue(), 1) << "dequeue not ordering properly";
  EXPECT_EQ(q1.dequeue(), 2) << "dequeue not ordering properly";
  testing::internal::CaptureStdout();
  q1.dequeue();
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "Removing 3\n") << "dequeue not printing properly";
}

TEST_F(QueueTest, Overflow) {
  Queue q1(1);
  q1.enqueue(1);
  EXPECT_EXIT(q1.enqueue(2),testing::ExitedWithCode(1),"") << "Overflow exit error";
  EXPECT_EXIT(q1.enqueue(3),testing::ExitedWithCode(1),"") << "second overflow error";
}

TEST_F(QueueTest, Underflow) {
  Queue q1(1);
  q1.enqueue(1);
  q1.dequeue();
  EXPECT_EXIT(q1.dequeue(),testing::ExitedWithCode(1),"") << "Underflow error not working";
}

TEST_F(QueueTest, Peek) {
  Queue q1(3);
  EXPECT_EXIT(q1.peek(),testing::ExitedWithCode(1),"") << "peeking at empty list weird";
  q1.enqueue(1);
  q1.enqueue(2);
  EXPECT_EQ(q1.peek(),1) << "peek is weird";
  q1.enqueue(3);
  EXPECT_EQ(q1.peek(),1) << "full peek() problem";
  q1.dequeue();
  EXPECT_EQ(q1.peek(),2) << "peek is weird";
  q1.enqueue(19);
  EXPECT_EQ(q1.peek(),2) << "peek is weird";
  q1.clear();
  EXPECT_EXIT(q1.peek(),testing::ExitedWithCode(1),"") << "peeking at emptied list not working";
}

TEST_F(QueueTest, Peek2) {
  Queue q3(1);
  Queue q4(0);
  testing::internal::CaptureStdout();
  EXPECT_EXIT(q3.peek(),testing::ExitedWithCode(1),"") << "peeking at capacity 0 list";
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  EXPECT_EXIT(q4.peek(),testing::ExitedWithCode(1),"") << "peeking at capacity 0 list";
  std::string output2 = testing::internal::GetCapturedStdout();
  
  EXPECT_EQ(output1,"Underflow\nProgram Terminated\n") << "peek error not working";
  EXPECT_EQ(output2,"Underflow\nProgram Terminated\n") << "peek error not working";
}



TEST_F(QueueTest, IndexOf) {
  Queue q1(3);
  EXPECT_EQ(q1.indexOf(5),-1) <<"indexOf empty queue";
  q1.enqueue(1);
  q1.enqueue(2);
  EXPECT_EQ(q1.indexOf(2),1) << "indexOf is weird";
  q1.dequeue();
  EXPECT_EQ(q1.indexOf(2),0) << "indexOf is weird";
  q1.enqueue(2);
  q1.enqueue(2);
  EXPECT_EQ(q1.indexOf(2),0) << "same number repeated for indexOf";
}

TEST_F(QueueTest, IndexOf2) {
  Queue q1(4);
  EXPECT_EQ(q1.indexOf(5),-1) <<"indexOf empty queue";
  q1.enqueue(1);
  q1.enqueue(2);
  q1.enqueue(3);
  q1.enqueue(4);
  q1.dequeue();
  q1.enqueue(5);
  EXPECT_EQ(q1.indexOf(1),-1) << "same number repeated for indexOf";
  EXPECT_EQ(q1.indexOf(5),3) << "indexOf 3";
  EXPECT_EQ(q1.indexOf(3),1) << "indexOf middle problem";
}

TEST_F(QueueTest, SizeAndCapacity) {
  Queue q1(0);
  EXPECT_EQ(q1.size(),0) << "size() not working";  
  EXPECT_EQ(q1.getCapacity(),0) << "getCapacity not working";
  Queue q2(99);
  q2.enqueue(4);
  q2.enqueue(6);
  q2.enqueue(4);
  q2.dequeue();
  q2.enqueue(4);
  q2.enqueue(4);
  EXPECT_EQ(q2.size(),4) << "size() not working";
  EXPECT_EQ(q2.getCapacity(),99) << "getCapacity not working";
}

TEST_F(QueueTest, MergeSort) {
  Queue q1(10);
  q1.enqueue(11);
  q1.enqueue(1);
  q1.enqueue(12);  
  q1.enqueue(4);
  q1.mergeSort();
  EXPECT_EQ(q1.dequeue(), 1) << "mergeSort not ordering properly";
  EXPECT_EQ(q1.dequeue(), 4) << "mergeSort not ordering properly";
  EXPECT_EQ(q1.dequeue(), 11) << "mergeSort not ordering properly";
  EXPECT_EQ(q1.dequeue(), 12) << "mergeSort not ordering properly";
  q1.clear();
  Queue q2(4);
  q2.enqueue(4);
  q2.enqueue(2);
  q2.enqueue(2);
  q2.enqueue(3);
  q2.mergeSort();
  EXPECT_EQ(q2.indexOf(4),3) << "mergesort problems";
  EXPECT_EQ(q2.indexOf(3),2) << "mergesort problems";
  EXPECT_EQ(q2.dequeue(),2) << "mergesort problems";
  EXPECT_EQ(q2.indexOf(2),0) << "mergesort problems";
  EXPECT_EQ(q2.size(),3) << "size after mergesort not working";
}

TEST_F(QueueTest, MergeSort2) {
  Queue q1(100);
  for (int i=0; i<100; ++i){
    q1.enqueue(1000-i);
  }
  for (int i=0; i<50; ++i){
    q1.dequeue();
  }
  for (int i=100; i<150; ++i){
    q1.enqueue(1000-i);
  }
  q1.mergeSort();
  for (int i=851; i<951; ++i){
    EXPECT_EQ(q1.dequeue(),i) << "mergeSort not ordering properly";
  }
}

TEST_F(QueueTest, Peek3) {
  Queue q1(100);
  for (int i=0; i<100; ++i){
    q1.enqueue(i);
  }
  for (int i=0; i<99; ++i){
    EXPECT_EQ(q1.peek(),i);
    q1.dequeue();
  }
  q1.enqueue(1);
  q1.dequeue();
  EXPECT_EQ(q1.peek(),1) << "peek not working";
}

TEST_F(QueueTest, Clearing4) {
  Queue q1(1000);
  q1.enqueue(5);
  q1.enqueue(2);
  q1.dequeue();
  for (int i=0; i<100; ++i){
    for (int j=0; j<2*i; ++j){
      q1.enqueue(j);
    }
    q1.clear();
    EXPECT_EXIT(q1.peek(),testing::ExitedWithCode(1),"") << "peeking after clearing";
  }
}

TEST_F(QueueTest, Clearing3) {
  Queue q1(100);
  for (int i=0; i<100; ++i){
    q1.enqueue(1000-i);
  }
  for (int i=0; i<50; ++i){
    q1.dequeue();
  }
  for (int i=100; i<150; ++i){
    q1.enqueue(1000-i);
  }
  q1.clear();
  EXPECT_EXIT(q1.peek(),testing::ExitedWithCode(1),"") << "peeking at capacity 0 list";
}

TEST_F(QueueTest, BubbleSort) {
  Queue q1(10);
  q1.enqueue(11);
  q1.enqueue(1);
  q1.enqueue(12);  
  q1.enqueue(4);
  q1.bubbleSort();
  EXPECT_EQ(q1.dequeue(), 1) << "bubbleSort not ordering properly";
  EXPECT_EQ(q1.dequeue(), 4) << "bubbleSort not ordering properly";
  EXPECT_EQ(q1.dequeue(), 11) << "bubbleSort not ordering properly";
  EXPECT_EQ(q1.dequeue(), 12) << "bubbleSort not ordering properly";
  q1.clear();
  Queue q2(4);
  q2.enqueue(4);
  q2.enqueue(2);
  q2.enqueue(2);
  q2.enqueue(3);
  q2.bubbleSort();
  EXPECT_EQ(q2.indexOf(4),3) << "bubblesort problems";
  EXPECT_EQ(q2.indexOf(3),2) << "bubblesort problems";
  EXPECT_EQ(q2.dequeue(),2) << "bubblesort problems";
  EXPECT_EQ(q2.indexOf(2),0) << "bubblesort problems";
  EXPECT_EQ(q2.size(),3) << "size() after bubbleSort not working";
}

TEST_F(QueueTest, SortingPeek) {
  Queue q2(4);
  q2.enqueue(4);
  q2.enqueue(2);
  q2.enqueue(1);
  q2.enqueue(3);
  q2.dequeue();
  q2.enqueue(1); //
  q2.mergeSort();
  EXPECT_EQ(q2.peek(),1) << "peek problems";
  EXPECT_EQ(q2.size(),4) << "peek problems";
  q2.clear();
  q2.enqueue(4);
  q2.enqueue(2);
  q2.enqueue(1);
  q2.enqueue(3);
  q2.dequeue();
  q2.bubbleSort();
  EXPECT_EQ(q2.peek(),1) << "peek problems";
}