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


//Testing Queue constructor
TEST_F(QueueTest, QueueConstructorTest) { 

  Queue capacityZeroQueue(0);  //Instantiating a queue with zero capacity  
  EXPECT_EQ(capacityZeroQueue.getCapacity(), 0); //checking whether capacity of queue is 0 as specificied in the constructor 
  EXPECT_EQ(capacityZeroQueue.isEmpty(), true);  //Since no elements were added to the Queue, it should be an empty queue 
  EXPECT_EQ(capacityZeroQueue.isFull(), true);  //Since capacity is zero and no elements were added, then this queue should be full
  EXPECT_EQ(sizeof(capacityZeroQueue), 4*sizeof(int) + sizeof(int*));  //Object Queue should be of size 24 bytes (4 ints and one 1 pointer)
  
  Queue capacityOneHundredQueue(100); //Instantiating a queue with capacity 100  
  EXPECT_EQ(capacityOneHundredQueue.getCapacity(), 100); //checking whether capacity of queue is 100 as specificied in the constructor  
  EXPECT_EQ(capacityOneHundredQueue.isEmpty(), true); //Since no elements were added to the Queue, it should be an empty queue  
  EXPECT_EQ(capacityOneHundredQueue.isFull(), false); //Since no elements were added to the Queue and capacity is 100, it should not be a full queue  
  EXPECT_EQ(sizeof(capacityOneHundredQueue), 4*sizeof(int) + sizeof(int*)); //Object Queue should be of size 24 (4 ints and one 1 pointer)  
}


//Testing dequeue method
TEST_F(QueueTest, dequeueTest) {
  
  Queue capacityFiveHundredQueue(500);  //initiating a queue of capcity 500
  for (int i = -250; i < 250; i++) {
    capacityFiveHundredQueue.enqueue(i);
  }

  //checking whether dequeue of all elements in the queue occurred properly
  int output;
  std::string output1;
  for (int i = -250; i < 250; i++) {
    testing::internal::CaptureStdout();
    output = capacityFiveHundredQueue.dequeue();
    output1 = testing::internal::GetCapturedStdout();    
    EXPECT_EQ(output, i); //checking whether popped value was correct
    EXPECT_EQ(output1, "Removing " +std::to_string(i)+"\n"); //checking if value is printed properly   
    EXPECT_EQ(capacityFiveHundredQueue.size(), 249-i);  //checking whether size is correct rigth after dequeing
  }

  //checking whether dequeue works properly when alternating with enqueue
  for (int i = 0; i < 500; i++) {
    capacityFiveHundredQueue.enqueue(i);
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(output, i);
  }
  
  EXPECT_EQ(capacityFiveHundredQueue.isEmpty(), true); //Since all elements were dequeed, then this queue should be an empty queue    
  
  //checking whether dequeing an empty queue will cause the program to exit with exit_failure code
  EXPECT_EXIT(capacityFiveHundredQueue.dequeue(), testing::ExitedWithCode(EXIT_FAILURE), "");
}

//Testing enqueue method
TEST_F(QueueTest, enqueueTest) {

  //initiating a queue of capcity 500
  Queue capacityFiveHundredQueue(500);
  std::string output1;
  for (int i = -250; i < 250; i++) {   
    testing::internal::CaptureStdout();
    capacityFiveHundredQueue.enqueue(i);
    output1 = testing::internal::GetCapturedStdout();   //checking if inserted value is correct     
    EXPECT_EQ(output1, "Inserting " +std::to_string(i)+"\n"); //checking if inserted value is printed correctly    
    EXPECT_EQ(capacityFiveHundredQueue.size(), i+251); //checking whether size is correct rigth after enqueing
  }

  //checking whether values were enqueued in the right order
  int output;
  for (int i = 0; i < 500; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(output, i-250);
  }

  //checking whether enqueue works properly when alternating with dequeue
  for (int i = 0; i < 500; i++) {
    capacityFiveHundredQueue.enqueue(i);
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(output, i);
  }
  
  //checking whether overflowing the queue will cause the program to exit with exit_failure code
  Queue capacityOneQueue(1);  
  capacityOneQueue.enqueue(1);
  EXPECT_EXIT(capacityOneQueue.enqueue(0), testing::ExitedWithCode(EXIT_FAILURE), "");  
}

//Testing peek method
TEST_F(QueueTest, peekTest) {
  
  int output;
  Queue capacityFiftyKQueue(50000); //initiating a queue of capacity 50000
  for (int i = -25000; i < 25000; i++) {
    capacityFiftyKQueue.enqueue(i);
    output = capacityFiftyKQueue.peek();
    EXPECT_EQ(output, -25000);       //regardless what was enqueued, peek should return the 0th elementh (i.e. -25000)
    EXPECT_EQ(capacityFiftyKQueue.size(), 25001+i);  //checking whether size is correct rigth after peeking    
    EXPECT_EQ(capacityFiftyKQueue.getCapacity(), 50000);  //checking whether capacity is correct rigth after peeking
  }

  //test peek behavior after a dequeue
  for (int i = -25000; i < 24999; i++) {    
    capacityFiftyKQueue.dequeue();
    output = capacityFiftyKQueue.peek();
    EXPECT_EQ(output, i+1);
  }
  
  //dequeing last element
  capacityFiftyKQueue.dequeue();
  EXPECT_EXIT(capacityFiftyKQueue.peek(), testing::ExitedWithCode(EXIT_FAILURE), "");
  
  //test peek behavior after an enqueue
  capacityFiftyKQueue.enqueue(-250);
  EXPECT_EQ(capacityFiftyKQueue.peek(), -250);
  
  //test peek behavior after clear queue;
  capacityFiftyKQueue.clear();
  EXPECT_EXIT(capacityFiftyKQueue.peek(), testing::ExitedWithCode(EXIT_FAILURE), "");  
  
  //checking whether peeking an empty queue will cause the program to exit with exit_failure code
  Queue capacityZeroQueue(0);
  EXPECT_EXIT(capacityZeroQueue.peek(), testing::ExitedWithCode(EXIT_FAILURE), "");
}


//Testing indexOf method
TEST_F(QueueTest, indexOfTest) {
  
  Queue capacityFiveHundredQueue(500); //initiating a queue of capacity 500
  for (int i = -250; i < 250; i++) {
    capacityFiveHundredQueue.enqueue(i);
  }

  //checking whether indexes are computed properly
  int output;
  for (int i = 0; i < 250; i++) {
    output = capacityFiveHundredQueue.indexOf(i);
    EXPECT_EQ(output, i+250);
  }
  
  //dequeue first 150 elements
  for(int i = -250; i < -100; i++) {
    capacityFiveHundredQueue.dequeue();
  }
  
  //check whether indexOf still works after dequeing
  for(int i = -100; i < 250; i++) {
    output = capacityFiveHundredQueue.indexOf(i);
    EXPECT_EQ(output, i+100);
  }
  
  for (int i = -250; i < -100; i++) {
    //values greater than -250 and less than -100 are not in the queue so the return value should be -1
    output = capacityFiveHundredQueue.indexOf(i);
    EXPECT_EQ(output, -1);  
  } 
}

//Testing size method
TEST_F(QueueTest, sizeTest) {
  
  Queue capacityFiveHundredQueue(500); //initiating a queue of capacity 500 
  EXPECT_EQ(capacityFiveHundredQueue.size(), 0);  //checking whether size is 0 before enqueing

  for (int i = 0; i < 500; i++) {
    capacityFiveHundredQueue.enqueue(i);  
    EXPECT_EQ(capacityFiveHundredQueue.size(), i+1);  //checking whether size is correct rigth after enqueing      
    EXPECT_GE(capacityFiveHundredQueue.getCapacity(), capacityFiveHundredQueue.size()); //capacity should always be greater or equal than size
  }
 
  int output;
  for (int i = 0; i < 500; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(capacityFiveHundredQueue.size(), 499-i);  //checking whether size is correct rigth after dequeing    
    EXPECT_GE(capacityFiveHundredQueue.getCapacity(), capacityFiveHundredQueue.size()); //capacity should always be greater or equal than size
  }
}


//Testing isEmpty method
TEST_F(QueueTest, isEmptyTest) {
  
  Queue capacityFiveHundredQueue(500); //initiating a queue of capacity 500  
  EXPECT_EQ(capacityFiveHundredQueue.isEmpty(), true); //checking whether queue is empty (it should be)

  for (int i = 0; i < 500; i++) {
    capacityFiveHundredQueue.enqueue(i);    
    EXPECT_EQ(capacityFiveHundredQueue.isEmpty(), false); //checking whether queue is empty (it shouldn't be)
  }

  //checking whether queue is empty (it shouldn't be) after dequeing
  //all but one element
  int output;
  for (int i = 0; i < 499; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(capacityFiveHundredQueue.isEmpty(), false);
  }
  output = capacityFiveHundredQueue.dequeue();
  
  //checking whether queue is empty after dequeing all elements ( it should be)
  EXPECT_EQ(capacityFiveHundredQueue.isEmpty(), true);
}

//Testing isFull method
TEST_F(QueueTest, isFullTest) {
  
  Queue capacityFiveHundredQueue(500); //initiating a queue of capacity 500 
  EXPECT_EQ(capacityFiveHundredQueue.isFull(), false);  //checking whether queue is full (it shouldn't be)

  for (int i = 0; i < 499; i++) {
    capacityFiveHundredQueue.enqueue(i);     
    EXPECT_EQ(capacityFiveHundredQueue.isFull(), false); //checking whether queue is full whe size < capacity (it shouldn't be)
  }
  capacityFiveHundredQueue.enqueue(499);  
  EXPECT_EQ(capacityFiveHundredQueue.isFull(), true); //checking whether queue is full whe size = capacity (it should be)

  //checking whether queue is full after dequeing (it shouldn't be)
  //all but one element
  int output;
  for (int i = 0; i < 500; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(capacityFiveHundredQueue.isFull(), false);
  }
}


//Testing getCapacity method
TEST_F(QueueTest, getCapacityTest) {
  
  Queue capacityFiveHundredQueue(500); //initiating a queue of capacity 500  
  EXPECT_EQ(capacityFiveHundredQueue.getCapacity(), 500); //checking whether capacity is 500 before enqueing

  for (int i = 0; i < 500; i++) {
    capacityFiveHundredQueue.enqueue(i);    
    EXPECT_EQ(capacityFiveHundredQueue.getCapacity(), 500); //checking whether capacity remains the same after enqueing
  }

  //checking whether capacity is correct rigth after dequeing
  int output;
  for (int i = 0; i < 500; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(capacityFiveHundredQueue.getCapacity(), 500);
  }
}


//Testing clear method
TEST_F(QueueTest, clearTest) {
  //initiating a queue of capacity 500
  Queue capacityFiveHundredQueue(500);
 
  for (int i = 0; i < 10; i++) {
    capacityFiveHundredQueue.enqueue(i);  
  }
  capacityFiveHundredQueue.clear();  
  
  EXPECT_EQ(capacityFiveHundredQueue.size(), 0); //size should be 0 after clear 
  EXPECT_EQ(capacityFiveHundredQueue.isEmpty(), true);  //queue should be empty  
  EXPECT_EQ(capacityFiveHundredQueue.isFull(), false); //queue should not be full 
  EXPECT_EQ(capacityFiveHundredQueue.getCapacity(), 500); // capacity should be the same after clear
}
 
  
 //Testing bubbleSort method
TEST_F(QueueTest, bubbleSortTest) {
  //initiating a queue of capacity 500. notice the value decreases with as the queue index increases
  Queue capacityFiveHundredQueue(500);
  for (int i = 499; i >= 0; i--) {
    capacityFiveHundredQueue.enqueue(i);    
  }
  
  capacityFiveHundredQueue.bubbleSort();
  
  //checking whether queue was ordered properly
  int output;
  for (int i = 0; i < 500; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(output, i);
  }  
}
 
 
 //Testing mergeSort method
TEST_F(QueueTest, mergeSortTest) {
   
  Queue capacityFiveHundredQueue(500); //initiating a queue of capacity 500.
  
  //inserting values in the queue. notice the value decreases with as the queue index increases
  for (int i = 499; i >= 0; i--) {
    capacityFiveHundredQueue.enqueue(i);    
  }
  
  capacityFiveHundredQueue.mergeSort();
  
  //checking whether queue was ordered properly
  int output;
  for (int i = 0; i < 500; i++) {
    output = capacityFiveHundredQueue.dequeue();
    EXPECT_EQ(output, i);
  }  
}
