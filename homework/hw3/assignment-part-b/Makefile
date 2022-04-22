CXX=g++
CXXFLAGS = -std=c++11 -g
DEP_DIR=/project/grades/Spring-2022/csci3081/dependencies

##### EDIT ME!!! #####################
# name of file in mutants
MAINQUEUEFILE = queue.cc
# name of correct file
CORRECTQUEUEFILE = queue.correct.cc 
# name of unittest file, for example test_suites/queue001/queue_unittest1.cc
MAINTESTFILE = queue_unittest.cc
######################################
# name of test executables
LABTESTEXE = queue_unittest
# name of main executable
LABEXE = queue

MUTANTS = $(patsubst mutants/mutant%/$(MAINQUEUEFILE),${LABTESTEXE}_m%,$(wildcard mutants/mutant*/$(MAINQUEUEFILE)))

all: ${LABEXE} ${LABTESTEXE}_correct $(MUTANTS)

${LABEXE}:
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -Iinclude -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib main.cc $(CORRECTQUEUEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

${LABTESTEXE}_correct: 
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -Iinclude -L$(DEP_DIR)/lib $(MAINTESTFILE) $(CORRECTQUEUEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

${LABTESTEXE}_m%: mutants/mutant%/$(MAINQUEUEFILE)
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -Iinclude -L$(DEP_DIR)/lib $(MAINTESTFILE) $< -lgtest_main -lgtest -lgmock -pthread -o $@

clean:
	rm -f ${LABEXE}
	rm -f ${LABTESTEXE}
	rm -f ${LABTESTEXE}_*
	rm -rf *.o
