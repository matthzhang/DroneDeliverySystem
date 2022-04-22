CXX=g++
CXXFLAGS = -std=c++11 -g
ROOT_DIR := $(shell git rev-parse --show-toplevel)
-include $(ROOT_DIR)/config/settings
-include $(DEP_DIR)/env

SOURCES = $(wildcard *.cc)
OBJFILES = $(notdir $(SOURCES:.cc=.o))

##### EDIT ME!!! #####################
MAINDATEFILE = date.cc
######################################
LABTESTEXE = date_unittest
LABEXE = date

all: ${LABEXE} 

${LABTESTEXE}: 
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -I. -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib date_unittest.cc $(MAINDATEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

${LABEXE}: ${LABTESTEXE}
	$(CXX) $(CXXFLAGS) -I$(DEP_DIR)/include  -I. -L$(DEP_DIR)/lib -L$(BUILD_DIR)/lib main.cc $(MAINDATEFILE) -lgtest_main -lgtest -lgmock -pthread -o $@

test: ${LABTESTEXE}

clean:
	rm -f ${LABEXE}
	rm -f ${LABTESTEXE}
	rm -rf *.o
