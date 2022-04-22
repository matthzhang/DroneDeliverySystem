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

TEST_F(QueueTest, constructorTest){
  Queue q(5);
  EXPECT_EQ(0, q.size());
  EXPECT_EQ(sizeof(q), 24);

}

TEST_F(QueueTest, enqueueTest){
  Queue q(5);
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(-1);
  EXPECT_EQ(1, q.peek()) << "Front of queue incorrect";
  EXPECT_EQ(2, q.indexOf(3)) << "3 placed in incorrect poisition";
  EXPECT_EQ(3, q.indexOf(-1)) << "Negative 1 did not work";

}

TEST_F(QueueTest, dequeueTest){
  Queue q(400);
  for(int i = 199; i >= -200; i--){
    q.enqueue(i);
  }
  q.bubbleSort();

  for(int i = -200; i < 200; i++){
    EXPECT_EQ(q.dequeue(), i);

  }

  q.enqueue(999999);
  q.enqueue(-999999);

  testing::internal::CaptureStdout();
  EXPECT_EQ(q.dequeue(), 999999);
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, "Removing 999999\n");
  EXPECT_EQ(q.dequeue(), -999999);


}

TEST_F(QueueTest, peekTest){

  Queue q(10);
  q.enqueue(10);
  q.enqueue(20);
  EXPECT_EQ(q.peek(), 10);
  q.enqueue(30);
  q.dequeue();
  EXPECT_EQ(q.peek(), 20);
  q.dequeue();
  EXPECT_EQ(q.peek(), 30);
  q.dequeue();
  q.enqueue(-1);
  EXPECT_EQ(q.peek(), -1);
}


TEST_F(QueueTest, indexOfTest){

  Queue q(250);
  EXPECT_EQ(q.indexOf(1), -1);

  for(int i = -100; i < 101; i++){
      q.enqueue(i);
  }

  int num = -100;

  for(int i = 0; i < 201; i++){
    EXPECT_EQ(q.indexOf(num), i);
    num++;
  }

  q.dequeue();
  q.dequeue();
  num = -98;
  for(int i = 0; i < 199; i++){
    EXPECT_EQ(q.indexOf(num), i);
    num++;
  }


  EXPECT_EQ(q.indexOf(1000), -1);
}

TEST_F(QueueTest, sizeTest){
  Queue q(1000);

  for(int i = 0; i < 100; i++){
    EXPECT_EQ(q.size(), i);
    q.enqueue(i);
  }

  for(int i = 99; i >= 0; i--){
    q.dequeue();
    EXPECT_EQ(q.size(), i);

  }



}


TEST_F(QueueTest, emptyTest){
  Queue q(50);
  Queue x(0);
  EXPECT_EQ(x.isEmpty(), true);
  EXPECT_EQ(q.isEmpty(), true);
  q.enqueue(1);
  EXPECT_EQ(q.isEmpty(), false);
  q.dequeue();
  EXPECT_EQ(q.isEmpty(), true);

  for(int i = 0; i < 50; i++){
    q.enqueue(i);
    EXPECT_EQ(q.isEmpty(), false);
  }

  for(int i = 0; i < 50; i++){
    q.dequeue();
  }

  EXPECT_EQ(q.isEmpty(), true);
}


TEST_F(QueueTest, fullTest){
  Queue x(0);
  EXPECT_EQ(x.isFull(), true);
  Queue q(50);
  EXPECT_EQ(q.isFull(), false);
  for(int i = 0; i < 50; i++){
    EXPECT_EQ(q.isFull(),false);
    q.enqueue(i);
  }
  EXPECT_EQ(q.isFull(), true);
  q.dequeue();
  EXPECT_EQ(q.isFull(), false);
}

TEST_F(QueueTest, capacityTest){

  Queue zero(0);
  EXPECT_EQ(zero.getCapacity(), 0);
  Queue fifty(50);
  EXPECT_EQ(fifty.getCapacity(), 50);
  fifty.enqueue(10);
  EXPECT_EQ(fifty.getCapacity(), 50);
}


TEST_F(QueueTest, clearTest){
  Queue q(10);
  q.enqueue(1);
  q.clear();
  EXPECT_EQ(q.size(), 0);
  EXPECT_EQ(q.getCapacity(), 10);
  q.enqueue(3);
  EXPECT_EQ(q.peek(), 3);

  Queue x(500);

  for(int i = -100; i < 400; i++){
    x.enqueue(i);
  }
    EXPECT_EQ(x.size(), 500);
    x.clear();

    EXPECT_EQ(x.size(), 0);

}

TEST_F(QueueTest, bubbleTest){
  Queue q(50);
  q.enqueue(7);
  q.enqueue(-1);
  q.enqueue(7);
  q.enqueue(50);
  q.bubbleSort();
  EXPECT_EQ(q.peek(), -1);
  EXPECT_EQ(q.dequeue(), -1);
  EXPECT_EQ(q.peek(), 7);
  EXPECT_EQ(q.dequeue(), 7);
  EXPECT_EQ(q.peek(), 7);
  EXPECT_EQ(q.dequeue(), 7);
  EXPECT_EQ(q.peek(), 50);
  EXPECT_EQ(q.dequeue(), 50);
  Queue x(200);

  for(int i = 100; i > -100; i--){
    x.enqueue(i);
  }

  x.bubbleSort();

  for(int i = -99; i <= 100; i++){
    EXPECT_EQ(x.peek(), i);
    EXPECT_EQ(x.dequeue(), i);

  }

}


TEST_F(QueueTest, mergeTest){
  Queue q(50);
  q.enqueue(7);
  q.enqueue(-1);
  q.enqueue(7);
  q.enqueue(50);
  q.mergeSort();
  EXPECT_EQ(q.peek(), -1);
  q.dequeue();
  EXPECT_EQ(q.peek(), 7);
  q.dequeue();
  EXPECT_EQ(q.peek(), 7);
  q.dequeue();
  EXPECT_EQ(q.peek(), 50);

  Queue x(200);

  for(int i = 100; i > -100; i--){
    x.enqueue(i);
  }

  x.mergeSort();

  for(int i = -99; i <= 100; i++){
    EXPECT_EQ(x.peek(), i);
    EXPECT_EQ(x.dequeue(), i);

  }
    EXPECT_EQ(x.isEmpty(), true);
}


TEST_F(QueueTest, overflowTest){

  Queue q(0);

  EXPECT_EXIT(q.enqueue(1), testing::ExitedWithCode(EXIT_FAILURE), "");


}
