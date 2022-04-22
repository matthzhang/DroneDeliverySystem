CXX=g++
CXXFLAGS = -std=c++11 -g
DEP_DIR=/project/grades/Spring-2022/csci3081/dependencies


all: queue_unittest queue

queue: queue.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib queue.o main.cc -o $@

queue_unittest: queue.o
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include -L$(DEP_DIR)/lib queue_unittest.cc queue.o -lgtest_main -lgtest -lgmock -pthread -o $@

clean:
	rm -f queue_unittest queue
