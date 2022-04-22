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

TEST_F(QueueTest, queueObjectSize) {  //Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  EXPECT_EQ(sizeof(q5), 24) << "queueObjectSize failure";

  Queue q1000;
  q1000.enqueue(1000);
  EXPECT_EQ(sizeof(q1000), 24) << "queueObjectSize failure";

  Queue q10(10);
  q10.enqueue(1);
  q10.dequeue();
  EXPECT_EQ(sizeof(q10), 24) << "queueObjectSize failure";

  Queue q0(0);
  EXPECT_EQ(sizeof(q0), 24) << "queueObjectSize failure";
}

TEST_F(QueueTest, copyConstructor) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  Queue test(q5);  //  copy q5 to test
  EXPECT_EQ(test.size(), 5) << "copyConstructor failure";

  Queue q1000;
  q1000.enqueue(1000);
  Queue test2(q1000);  //  copy q1000 to test
  EXPECT_EQ(test2.size(), 1) << "copyConstructor failure";

  Queue q10(10);
  q10.enqueue(1);
  q10.dequeue();
  Queue test3(q10);  //  copy q10 to test
  EXPECT_EQ(test3.size(), 0) << "copyConstructor failure";

  Queue q0(0);
  Queue test4(q0);  //  copy q0 to test
  EXPECT_EQ(test4.size(), 0) << "copyConstructor failure";
}

TEST_F(QueueTest, operatorEqual) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  Queue test = q5;  //  copy q5 to test
  EXPECT_EQ(test.size(), 5) << "operatorEqual failure";

  Queue q1000;
  q1000.enqueue(1000);
  test = q1000;  //  copy q1000 to test
  EXPECT_EQ(test.size(), 1) << "operatorEqual failure";

  Queue q10(10);
  q10.enqueue(1);
  q10.dequeue();
  test = q10;  //  copy q10 to test
  EXPECT_EQ(test.size(), 0) << "operatorEqual failure";

  Queue q0(0);
  test = q0;  //  copy q0 to test
  EXPECT_EQ(test.size(), 0) << "operatorEqual failure";
}

TEST_F(QueueTest, dequeueTest) {  //  Passes
  Queue q2(2);
  q2.enqueue(2);
  q2.enqueue(1);
  std::string expected_out_1 = "Removing 2\n";
  testing::internal::CaptureStdout();
  q2.dequeue();
  std::string output1 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output1, expected_out_1);

  Queue q1000;
  q1000.enqueue(1000);
  q1000.enqueue(1002);
  std::string expected_out_2 = "Removing 1000\n";
  testing::internal::CaptureStdout(); // You must do this EVERY TIME, or else it will segfault
  q1000.dequeue();
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output2, expected_out_2);
  EXPECT_EQ(q1000.dequeue(), 1002) << "dequeue failure";


  // Test for Underflow
  Queue q0(0); 
  // std::string expected_out_3 = "2018-10-31\n";
  // testing::internal::CaptureStdout();
  // q0.dequeue();
  // std::string output3 = testing::internal::GetCapturedStdout();
  // EXPECT_EQ(output3, expected_out_3);
  EXPECT_EXIT(q0.dequeue(), testing::ExitedWithCode(EXIT_FAILURE), "") << "dequeue failure";

}

TEST_F(QueueTest, enqueueTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  EXPECT_EQ(q5.size(), 5) << "enqueue failure";

  Queue q1000;
  q1000.enqueue(1000);
  EXPECT_EQ(q1000.size(), 1) << "enqueue failure";

  // Test negative vals
  Queue q10(10);
  q10.enqueue(-1);
  EXPECT_EQ(q10.size(), 1) << "enqueue failure";

  // Test Overflow enqueue
  Queue q0(0);
  EXPECT_EXIT(q0.enqueue(1), testing::ExitedWithCode(EXIT_FAILURE), "") << "enqueue failure";

}

TEST_F(QueueTest, peekTest) {  //  one unlucky situation where peek() fails
  Queue q5 = Queue(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  q5.peek();
  EXPECT_EQ(q5.peek(), 1) << "peek failure";

  Queue q1000;
  q1000.enqueue(-1000);
  EXPECT_EQ(q1000.peek(), -1000) << "peek failure";

  //  Test Underflow (from peek)
  Queue q10(10);
  q10.enqueue(1);
  q10.enqueue(2);
  Queue test2 = q10;
  q10.dequeue();
  EXPECT_NE(q10.peek(), test2.peek());
  //EXPECT_EXIT(q10.peek(), testing::ExitedWithCode(EXIT_FAILURE), "") << "peek failure";
  EXPECT_EQ(q10.peek(), 2);

  Queue q0(15);
  for(int i = 0; i < 15; i++){
    q0.enqueue(i);
  }
  for(int j = 0; j < 15; j++){
    q0.dequeue();
    if (j == 12){
      //EXPECT_EXIT(q0.peek(), testing::ExitedWithCode(EXIT_FAILURE), "") << "peek failure";
      EXPECT_EQ(q0.peek(), 13);
    } 
  }
}

TEST_F(QueueTest, indexOfTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  EXPECT_EQ(q5.indexOf(2), 1) << "indexOf failure";

  Queue q1000;
  q1000.enqueue(1000);
  EXPECT_EQ(q1000.indexOf(-2), -1) << "indexOf failure";

  Queue q10(10);
  q10.enqueue(1);
  q10.dequeue();
  EXPECT_EQ(q10.indexOf(1), -1) << "indexOf failure";

  Queue q0(0);
  EXPECT_EQ(q0.indexOf(0), -1) << "indexOf failure";
}

TEST_F(QueueTest, sizeTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  EXPECT_EQ(q5.size(), 5) << "sizeTest failure";

  Queue q1000;
  q1000.enqueue(1000);
  EXPECT_EQ(q1000.size(), 1) << "sizeTest failure";

  Queue q10(10);
  q10.enqueue(1);
  q10.dequeue();
  EXPECT_EQ(q10.size(), 0) << "sizeTest failure";

  Queue q0(0);
  EXPECT_EQ(q0.size(), 0) << "sizeTest failure";

}

TEST_F(QueueTest, isEmptyTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(2);
  EXPECT_EQ(q5.isEmpty(), false) << "isEmpty failure";

  Queue q1000;
  EXPECT_EQ(q1000.isEmpty(), true) << "isEmpty failure";

  Queue q10(10);
  q10.enqueue(2);
  q10.dequeue();
  EXPECT_EQ(q10.isEmpty(), true) << "isEmpty failure";

  Queue q3(3);
  q3.enqueue(3);
  EXPECT_EQ(q3.isEmpty(), false) << "isEmpty failure";

}

TEST_F(QueueTest, isFullTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  EXPECT_EQ(q5.isFull(), true) << "isFull failure";

  Queue q1000;
  for (int i = 0; i < 1000; i++) {
    q1000.enqueue(i);
  }
  EXPECT_EQ(q1000.isFull(), true) << "isFull failure";

  Queue q10(10);
  q10.enqueue(1);
  EXPECT_EQ(q10.isFull(), false) << "isFull failure";

  Queue q0(0);
  EXPECT_EQ(q0.isFull(), true) << "isFull failure";
}

TEST_F(QueueTest, getCapacityTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  EXPECT_EQ(q5.getCapacity(), 5) << "getCapacity failure";

  Queue q1000;
  q1000.enqueue(1000);
  EXPECT_EQ(q1000.getCapacity(), 1000) << "getCapacity failure";

  // Test negative vals
  // Queue q10(-10);
  // EXPECT_EQ(q10.getCapacity(), ERROR) << "getCapacity failure";

  Queue q0(0);
  EXPECT_EQ(q0.getCapacity(), 0) << "getCapacity failure";
}

TEST_F(QueueTest, clearTest) {  //  Passes
  Queue q5(5);
  q5.enqueue(1);
  q5.enqueue(2);
  q5.enqueue(3);
  q5.enqueue(4);
  q5.enqueue(5);
  q5.clear();
  EXPECT_EQ(q5.size(), 0) << "clear failure";
  EXPECT_EQ(q5.getCapacity(), 5) << "clear failure";
  EXPECT_EQ(q5.indexOf(2), -1) << "clear failure";

  Queue q1000;
  q1000.enqueue(1000);
  q1000.clear();
  EXPECT_EQ(q1000.size(), 0) << "clear failure";
  EXPECT_EQ(q1000.getCapacity(), 1000) << "clear failure";
  EXPECT_EQ(q1000.indexOf(1000), -1) << "clear failure";

  Queue q10(10);
  q10.enqueue(1);
  q10.clear();
  EXPECT_EQ(q10.size(), 0) << "clear failure";
  EXPECT_EQ(q10.getCapacity(), 10) << "clear failure";
  EXPECT_EQ(q10.indexOf(1), -1) << "clear failure";

  Queue q0(0);
  q0.clear();
  EXPECT_EQ(q0.size(), 0) << "clear failure";
  EXPECT_EQ(q0.getCapacity(), 0) << "clear failure";
  EXPECT_EQ(q0.indexOf(1), -1) << "clear failure";
}

TEST_F(QueueTest, bubbleSortTest) {  //  Passes
  int test[6] = {10, 5, 21, 0, 17, 1};
  //  int testAns = [0, 1, 5, 10, 17, 21];
  Queue q1(6);
  for (int i = 0; i < 6; i++) {
    q1.enqueue(test[i]);
  }
  q1.bubbleSort();
  EXPECT_EQ(q1.indexOf(0), 0) << "bubblesort failure";
  EXPECT_EQ(q1.indexOf(1), 1) << "bubblesort failure";
  EXPECT_EQ(q1.indexOf(5), 2) << "bubblesort failure";
  EXPECT_EQ(q1.indexOf(10), 3) << "bubblesort failure";
  EXPECT_EQ(q1.indexOf(17), 4) << "bubblesort failure";
  EXPECT_EQ(q1.indexOf(21), 5) << "bubblesort failure";

  int test2[5] = {16, -19, 9, 18, 15};
  //  int test2Ans = [-19, 9, 15, 16, 18];
  Queue q2(6);
  for (int i = 0; i < 5; i++) {
    q2.enqueue(test2[i]);
  }
  q2.bubbleSort();
  EXPECT_EQ(q2.indexOf(-19), 0) << "bubblesort failure";
  EXPECT_EQ(q2.indexOf(9), 1) << "bubblesort failure";
  EXPECT_EQ(q2.indexOf(15), 2) << "bubblesort failure";
  EXPECT_EQ(q2.indexOf(16), 3) << "bubblesort failure";
  EXPECT_EQ(q2.indexOf(18), 4) << "bubblesort failure";

  int test3[4] = {1, 3, 5, 9};
  //  int test3Ans = [1, 3, 5, 9];
  Queue q3(6);
  for (int i = 0; i < 4; i++) {
    q3.enqueue(test3[i]);
  }
  q3.bubbleSort();
  EXPECT_EQ(q3.indexOf(1), 0) << "bubblesort failure";
  EXPECT_EQ(q3.indexOf(3), 1) << "bubblesort failure";
  EXPECT_EQ(q3.indexOf(5), 2) << "bubblesort failure";
  EXPECT_EQ(q3.indexOf(9), 3) << "bubblesort failure";

  Queue q4;
  q4.enqueue(1);
  q4.bubbleSort();
  EXPECT_EQ(q4.indexOf(1), 0) << "bubblesort failure";
}

TEST_F(QueueTest, mergeSortTest) {  //  Passes
  int test[6] = {10, 5, 21, 0, 17, 1};
  //  int testAns = [0, 1, 5, 10, 17, 21];
  Queue q1(6);
  for (int i = 0; i < 6; i++) {
    q1.enqueue(test[i]);
  }
  q1.mergeSort();
  EXPECT_EQ(q1.indexOf(0), 0) << "mergeSort failure";
  EXPECT_EQ(q1.indexOf(1), 1) << "mergeSort failure";
  EXPECT_EQ(q1.indexOf(5), 2) << "mergeSort failure";
  EXPECT_EQ(q1.indexOf(10), 3) << "mergeSort failure";
  EXPECT_EQ(q1.indexOf(17), 4) << "mergeSort failure";
  EXPECT_EQ(q1.indexOf(21), 5) << "mergeSort failure";

  int test2[5] = {16, -19, 9, 18, 15};
  //  int test2Ans = [-19, 9, 15, 16, 18];
  Queue q2(5);
  for (int i = 0; i < 5; i++) {
    q2.enqueue(test2[i]);
  }
  q2.mergeSort();
  EXPECT_EQ(q2.indexOf(-19), 0) << "mergeSort failure";
  EXPECT_EQ(q2.indexOf(9), 1) << "mergeSort failure";
  EXPECT_EQ(q2.indexOf(15), 2) << "mergeSort failure";
  EXPECT_EQ(q2.indexOf(16), 3) << "mergeSort failure";
  EXPECT_EQ(q2.indexOf(18), 4) << "mergeSort failure";

  int test3[4] = {1, 3, 5, 9};
  //  int test3Ans = [1, 3, 5, 9];
  Queue q3(4);
  for (int i = 0; i < 4; i++) {
    q3.enqueue(test3[i]);
  }
  q3.mergeSort();
  EXPECT_EQ(q3.indexOf(1), 0) << "mergeSort failure";
  EXPECT_EQ(q3.indexOf(3), 1) << "mergeSort failure";
  EXPECT_EQ(q3.indexOf(5), 2) << "mergeSort failure";
  EXPECT_EQ(q3.indexOf(9), 3) << "mergeSort failure";

  Queue q4(1);
  q4.enqueue(1);
  q4.mergeSort();
  EXPECT_EQ(q4.indexOf(1), 0) << "mergeSort failure";

  // Queue q7;
  // EXPECT_EXIT(q7.mergeSort(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

