CXX=g++
CXXFLAGS=-std=c++11 -Wall
OMPFLAGS=-fopenmp

SRC=$(wildcard *.cpp)
BIN_DIR=../bin
BIN=$(basename $(SRC))
INC_DIR=../include
INC=$(wildcard $(INC_DIR)/*.h)

PARALLEL_FILES=$(wildcard *parallel*.cpp)

.PHONY: all clean

all: $(BIN)

%: %.cpp $(INC)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) $(filter-out $(PARALLEL_FILES), $^) -o $(BIN_DIR)/$@
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -I $(INC_DIR) $(filter $(PARALLEL_FILES), $^) -o $(BIN_DIR)/$@ $(LDLIBS)

clean:
	$(RM) -r $(addprefix $(BIN_DIR)/, $(BIN)) *~*~
