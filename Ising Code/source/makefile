CXX=g++
CXXFLAGS=-std=c++11 -Wall
OMPFLAGS=-fopenmp

SRC=$(wildcard *.cpp)
BIN_DIR=../bin
BIN=$(basename $(SRC))
INC_DIR=../include
INC=$(wildcard $(INC_DIR)/*.h)

PARALLEL_FILES=$(wildcard *parallel*.cpp)
NON_PARALLEL_FILES=$(filter-out $(PARALLEL_FILES), $(SRC))

.PHONY: all clean

all: $(BIN)

%: %.cpp $(INC)
	mkdir -p $(BIN_DIR)
ifneq ($(strip $(NON_PARALLEL_FILES)),)
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) $(filter %.cpp, $^) -o $(BIN_DIR)/$@
endif
ifneq ($(strip $(PARALLEL_FILES)),)
	$(CXX) $(CXXFLAGS) $(OMPFLAGS) -I $(INC_DIR) $(filter %.cpp, $^) -o $(BIN_DIR)/$@ $(OMPFLAGS)
endif

clean:
	$(RM) -r $(addprefix $(BIN_DIR)/, $(BIN)) *~*~
