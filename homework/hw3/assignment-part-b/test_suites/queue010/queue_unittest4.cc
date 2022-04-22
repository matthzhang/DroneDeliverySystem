#include "gtest/gtest.h"
#include "queue.h"

class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) {
    // code here will execute just before the test ensues
    q1 = new Queue(1);
    q4 = new Queue(4);
  }
  void TearDown() {
    // code here will execute just after the test ends
  }
 protected:
    Queue *q1;
    Queue *q4;
};

TEST_F(QueueTest, ConstructorTests) {
    Queue *q1000 = new Queue();

    EXPECT_EQ(q1000->getCapacity(), 1000);
    EXPECT_EQ(q1000->size(), 0);
    EXPECT_EQ(q1->getCapacity(), 1) << "Constructor or getCapacity not working";
    EXPECT_EQ(q1->size(), 0);
    EXPECT_EQ(q4->getCapacity(), 4) << "Constructor or getCapacity not working";
    EXPECT_EQ(q4->size(), 0);
}

TEST_F(QueueTest, DequeueTests) {
    std::string expected_out_1 = "Removing 1\n";
    std::string expected_out_2 = "Removing 2\n";
    std::string expected_out_3 = "Removing 3\n";
    std::string expected_out_4 = "Removing 4\n";

    q1->enqueue(1);
    testing::internal::CaptureStdout();
    q1->dequeue();
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output1, expected_out_1) << "Dequeue not working";
    // EXPECT_EXIT(q1->dequeue(), testing::ExitedWithCode(EXIT_FAILURE), "");

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);

    testing::internal::CaptureStdout();
    q4->dequeue();
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output2, expected_out_1);

    testing::internal::CaptureStdout();
    q4->dequeue();
    std::string output3 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output3, expected_out_2);

    testing::internal::CaptureStdout();
    q4->dequeue();
    std::string output4 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output4, expected_out_3);

    testing::internal::CaptureStdout();
    q4->dequeue();
    std::string output5 = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output5, expected_out_4);

    // EXPECT_EXIT(q4->dequeue(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST_F(QueueTest, EnqueueTests) {
    q1->enqueue(1);
    EXPECT_EQ(q1->peek(), 1) << "Enqueue or peek not working";

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    EXPECT_EQ(q4->peek(), 1) << "Enqueue with multiple adds or peek not working";
    EXPECT_EQ(q4->indexOf(4), 3) << "Enqueue with multiple adds or indexOf not working";

    EXPECT_EXIT(q4->enqueue(5), testing::ExitedWithCode(EXIT_FAILURE), "");
}

TEST_F(QueueTest, PeekTests) {
    q1->enqueue(1);
    EXPECT_EQ(q1->peek(), 1);

    q4->enqueue(1);
    q4->enqueue(2);
    EXPECT_EQ(q4->peek(), 1);

    q4->dequeue();
    EXPECT_EQ(q4->peek(), 2);

    q4->dequeue();
    EXPECT_EXIT(q4->peek(), testing::ExitedWithCode(EXIT_FAILURE), "");

    Queue *q1000 = new Queue();
    for (int i = -500; i < 500; i++) {
        q1000->enqueue(i);
    }

    for (int i = -500; i < 500; i++) {
        EXPECT_EQ(q1000->peek(), i);
        q1000->dequeue();
    }
}

TEST_F(QueueTest, IndexOfTests) {
    Queue *q3 = new Queue(3);

    q3->enqueue(1);
    q3->enqueue(2);
    q3->enqueue(3);

    EXPECT_EQ(q3->indexOf(1), 0);
    EXPECT_EQ(q3->indexOf(2), 1);
    EXPECT_EQ(q3->indexOf(3), 2);
    EXPECT_EQ(q3->indexOf(4), -1);

    q3->dequeue();

    EXPECT_EQ(q3->indexOf(1), -1);
    EXPECT_EQ(q3->indexOf(2), 0);
    EXPECT_EQ(q3->indexOf(3), 1);
}

TEST_F(QueueTest, SizeTests) {
    EXPECT_EQ(q1->size(), 0);
    q1->enqueue(1);
    EXPECT_EQ(q1->size(), 1);

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    EXPECT_EQ(q4->size(), 4);
}

TEST_F(QueueTest, IsEmptyTests) {
    EXPECT_EQ(q1->isEmpty(), true);
    EXPECT_EQ(q4->isEmpty(), true);

    q1->enqueue(1);
    EXPECT_EQ(q1->isEmpty(), false);

    q1->dequeue();
    EXPECT_EQ(q1->isEmpty(), true);

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    EXPECT_EQ(q4->isEmpty(), false);
}

TEST_F(QueueTest, IsFullTests) {
    EXPECT_EQ(q1->isFull(), false);
    q1->enqueue(1);
    EXPECT_EQ(q1->isFull(), true);

    q4->enqueue(1);
    EXPECT_EQ(q4->isFull(), false);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    EXPECT_EQ(q4->isFull(), true);
}

TEST_F(QueueTest, GetCapacityTests) {
    Queue *q1000 = new Queue();

    EXPECT_EQ(q1000->getCapacity(), 1000);
    EXPECT_EQ(q1->getCapacity(), 1);
    EXPECT_EQ(q4->getCapacity(), 4);

    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    EXPECT_EQ(q4->getCapacity(), 4);
}

TEST_F(QueueTest, ClearTests) {
    q1->clear();
    EXPECT_EQ(q1->getCapacity(), 1);
    EXPECT_EQ(q1->size(), 0);

    q1->enqueue(1);
    q1->clear();
    EXPECT_EQ(q1->getCapacity(), 1);
    EXPECT_EQ(q1->size(), 0);

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    q4->clear();
    EXPECT_EQ(q4->getCapacity(), 4);
    EXPECT_EQ(q4->size(), 0);
}

TEST_F(QueueTest, BubbleSortTests) {
    q1->bubbleSort();
    EXPECT_EQ(q1->size(), 0);

    q1->enqueue(1);
    q1->bubbleSort();
    EXPECT_EQ(q1->peek(), 1);

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    q4->bubbleSort();
    EXPECT_EQ(q4->indexOf(1), 0);
    EXPECT_EQ(q4->indexOf(2), 1);
    EXPECT_EQ(q4->indexOf(3), 2);
    EXPECT_EQ(q4->indexOf(4), 3);

    Queue *q8 = new Queue(8);
    q8->enqueue(5);
    q8->enqueue(3);
    q8->enqueue(4);
    q8->enqueue(8);
    q8->enqueue(1);
    q8->enqueue(7);
    q8->enqueue(6);
    q8->enqueue(2);
    q8->bubbleSort();
    EXPECT_EQ(q8->indexOf(1), 0);
    EXPECT_EQ(q8->indexOf(2), 1);
    EXPECT_EQ(q8->indexOf(3), 2);
    EXPECT_EQ(q8->indexOf(4), 3);
    EXPECT_EQ(q8->indexOf(5), 4);
    EXPECT_EQ(q8->indexOf(6), 5);
    EXPECT_EQ(q8->indexOf(7), 6);
    EXPECT_EQ(q8->indexOf(8), 7);
}

TEST_F(QueueTest, MergeSortTests) {
    q1->mergeSort();
    EXPECT_EQ(q1->size(), 0);

    q1->enqueue(1);
    q1->mergeSort();
    EXPECT_EQ(q1->peek(), 1);

    q4->enqueue(1);
    q4->enqueue(2);
    q4->enqueue(3);
    q4->enqueue(4);
    q4->mergeSort();
    EXPECT_EQ(q4->indexOf(1), 0);
    EXPECT_EQ(q4->indexOf(2), 1);
    EXPECT_EQ(q4->indexOf(3), 2);
    EXPECT_EQ(q4->indexOf(4), 3);

    Queue *q8 = new Queue(8);
    q8->enqueue(5);
    q8->enqueue(3);
    q8->enqueue(4);
    q8->enqueue(8);
    q8->enqueue(1);
    q8->enqueue(7);
    q8->enqueue(6);
    q8->enqueue(2);
    q8->mergeSort();
    EXPECT_EQ(q8->indexOf(1), 0);
    EXPECT_EQ(q8->indexOf(2), 1);
    EXPECT_EQ(q8->indexOf(3), 2);
    EXPECT_EQ(q8->indexOf(4), 3);
    EXPECT_EQ(q8->indexOf(5), 4);
    EXPECT_EQ(q8->indexOf(6), 5);
    EXPECT_EQ(q8->indexOf(7), 6);
    EXPECT_EQ(q8->indexOf(8), 7);
}

TEST_F(QueueTest, QueueSizeTests) {
    Queue q3 = Queue(3);
    EXPECT_EQ(sizeof(q3), 24);
}