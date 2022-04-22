#include "gtest/gtest.h"
#include "queue.h"
#include <climits>

#include <algorithm>
#include <string>
#include <malloc.h>

class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    // code here will execute just before the test ensues 
    q = new Queue(5);
    
    q->enqueue(24);
    q->enqueue(42);
    q->enqueue(38);
    q->enqueue(15);
  }
  void TearDown() {
  	q->clear();
  	delete q;
    // code here will execute just after the test ends
  }
 protected:
	Queue* q;
};


TEST_F(QueueTest, TestIndexOf) {
	EXPECT_EQ(q->indexOf(24), 0) << "indexOf is broken";
	EXPECT_EQ(q->indexOf(42), 1) << "indexOf is broken";
	EXPECT_EQ(q->indexOf(38), 2) << "indexOf is broken";
	EXPECT_EQ(q->indexOf(15), 3) << "indexOf is broken";
	EXPECT_EQ(q->indexOf(69), -1) << "indexOf is broken";
}

TEST_F(QueueTest, TestGetCapacity) {
	EXPECT_EQ(q->getCapacity(), 5) << "GetCapacity is broken";
}

TEST_F(QueueTest, TestSize) {
	EXPECT_EQ(q->size(), 4) << "GetSize is broken";
	q->enqueue(8);
	EXPECT_EQ(q->size(), 5) << "GetSize is broken";
}

TEST_F(QueueTest, TestBubbleSort) {
	q->bubbleSort();
	EXPECT_EQ(q->indexOf(15), 0) << "BubbleSort is broken";
	EXPECT_EQ(q->indexOf(24), 1) << "BubbleSort is broken";
	EXPECT_EQ(q->indexOf(38), 2) << "BubbleSort is broken";
	EXPECT_EQ(q->indexOf(42), 3) << "BubbleSort is broken";
}

TEST_F(QueueTest, TestMergeSort) {
	q->mergeSort();
	EXPECT_EQ(q->indexOf(15), 0) << "BubbleSort is broken";
	EXPECT_EQ(q->indexOf(24), 1) << "BubbleSort is broken";
	EXPECT_EQ(q->indexOf(38), 2) << "BubbleSort is broken";
	EXPECT_EQ(q->indexOf(42), 3) << "BubbleSort is broken";
}

TEST_F(QueueTest, TestPeak) {
	EXPECT_EQ(q->peek(), 24) << "Peak is broken";
	q->dequeue();
	EXPECT_EQ(q->peek(), 42) << "Peak is broken";
	q->dequeue();
	EXPECT_EQ(q->peek(), 38) << "Peak is broken";
	q->dequeue();
	EXPECT_EQ(q->peek(), 15) << "Peak is broken";
	q->dequeue();
}

TEST_F(QueueTest, TestDequeue) {
	EXPECT_EQ(q->dequeue(), 24) << "Dequeue is broken";
	EXPECT_EQ(q->dequeue(), 42) << "Dequeue is broken";
	EXPECT_EQ(q->dequeue(), 38) << "Dequeue is broken";
	EXPECT_EQ(q->dequeue(), 15) << "Dequeue is broken";
}

TEST_F(QueueTest, TestIsFull) {
	q->enqueue(1234);
	EXPECT_EQ(q->isFull(), true) << "isFull is broken";
}

TEST_F(QueueTest, TestIsEmpty) {
	q->clear();
	EXPECT_EQ(q->isEmpty(), true) << "isEmpty is broken";
}

TEST_F(QueueTest, TestWrongSize) {
	Queue* asdf = new Queue(6);
	EXPECT_EQ(asdf->size(), 0) << "size is broken";
	asdf->enqueue(INT_MAX);
	EXPECT_EQ(asdf->size(), 1) << "size is broken";
	asdf->enqueue(INT_MAX);
	EXPECT_EQ(asdf->size(), 2) << "size is broken";
	asdf->enqueue(INT_MAX);
	EXPECT_EQ(asdf->size(), 3) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
	
	EXPECT_EQ(asdf->size(), 2) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
	
	EXPECT_EQ(asdf->size(), 1) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
	
	EXPECT_EQ(asdf->size(), 0) << "size is broken";
	
	
	asdf->enqueue(INT_MIN);
	EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->size(), 1) << "size is broken";
	
	asdf->enqueue(INT_MAX);
	EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->size(), 2) << "size is broken";
	
	asdf->enqueue(INT_MIN);
	EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->size(), 3) << "size is broken";
	
	asdf->enqueue(INT_MIN);
	EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->size(), 4) << "size is broken";
	
	asdf->enqueue(INT_MAX);
	EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->size(), 5) << "size is broken";
	
	asdf->enqueue(INT_MAX);
	EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->size(), 6) << "size is broken";
	
	
	EXPECT_EQ(asdf->dequeue(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MIN) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
	EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
	
	asdf->enqueue(INT_MAX);
	asdf->clear();
	EXPECT_EQ(asdf->size(), 0) << "size is broken";
	
//	asdf->enqueue(INT_MAX);
//	asdf->clear();
//	EXPECT_EQ(asdf->size(), 0) << "size is broken";
//	
//	asdf->enqueue(INT_MAX);
//	asdf->clear();
//	EXPECT_EQ(asdf->size(), 0) << "size is broken";
//	
//	for(int i = 0; i<10; i++) {
//		asdf->enqueue(INT_MAX);
//		asdf->enqueue(INT_MIN);
//		EXPECT_EQ(asdf->peek(), INT_MAX) << "size is broken";
//		EXPECT_EQ(asdf->dequeue(), INT_MAX) << "size is broken";
//		EXPECT_EQ(asdf->peek(), INT_MIN) << "size is broken";
//		EXPECT_EQ(asdf->dequeue(), INT_MIN) << "size is broken";
//	}
	

}


TEST_F(QueueTest, TestWrongPeek) {
	Queue* asdf = new Queue(100);
	
	for(int i = 1; i<3; i++) {
		for(int i = 1; i<=100; i++) {
			asdf->enqueue(i %7);
		}
		EXPECT_EQ(asdf->size(), 100) << "size is broken";
		EXPECT_EQ(asdf->peek(), 1) << "size is broken";
		
		for(int i = 1; i<=100; i++) {
			EXPECT_EQ(asdf->peek(), i%7) << "size is broken";
			EXPECT_EQ(asdf->dequeue(), i%7) << "size is broken";
		}
	}
}


TEST_F(QueueTest, TestWrongDequeue) {
	Queue* asdf = new Queue(100);
	
	asdf->enqueue(3);
	testing::internal::CaptureStdout();
	
	asdf->dequeue();
	std::string output = testing::internal::GetCapturedStdout();
	output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
	
	EXPECT_EQ(output ,"Removing 3") << "asdf";
	asdf->clear();
	
	
	


	
	
	
}

TEST_F(QueueTest, TestOverflow) {
	Queue* asdf = new Queue(1);
	asdf->enqueue(3);
	EXPECT_EXIT(asdf->enqueue(3) , testing::ExitedWithCode(1) , "") << "asdf";
}

TEST_F(QueueTest, TestMoreSpace) {

	Queue* asdf = new Queue(100000);
	for(int i= 0; i<9999; i++) {
		asdf->enqueue(3);
	}
	EXPECT_EQ(sizeof(*asdf), 24) << "size is broken";
}






