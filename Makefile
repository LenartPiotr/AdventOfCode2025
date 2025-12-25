CXX      := g++
CXXFLAGS := -std=c++2a -Wall -Wextra -O3 -Iinclude
LDFLAGS  := 

SRC_DIR := src
OUT_DIR := out

LIB_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
LIB_OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OUT_DIR)/%.o, $(LIB_SOURCES))

DAYS    := 2 3 4 5 6 7
TARGETS := $(patsubst %, $(OUT_DIR)/day%.exe, $(DAYS))

all: $(TARGETS)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUT_DIR)/day%.exe: day%.cpp $(LIB_OBJECTS)
	$(CXX) $(CXXFLAGS) $< $(LIB_OBJECTS) -o $@ $(LDFLAGS)

run:
	@./$(OUT_DIR)/day$(DAY).exe

clean:
	rm -rf $(OUT_DIR)

.PHONY: all prepare clean run