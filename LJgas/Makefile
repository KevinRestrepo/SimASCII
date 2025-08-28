CXX = g++
CXXFLAGS = -Wall -std=c++17 -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/%.o, $(SRC))
MAIN_SRC = main.cpp
MAIN_OBJ = build/main.o
TESTS = $(wildcard tests/*.cpp)
TEST_OBJ = $(patsubst tests/%.cpp, build/%.test.o, $(TESTS))
TARGET = main
TEST_TARGET = test
PLOT_TARGET = plot

.PHONY: all test clean

all: $(TARGET)

$(TARGET): $(OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MAIN_OBJ): $(MAIN_SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $^
	./$(TEST_TARGET)

build/%.test.o: tests/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET) $(TEST_TARGET) $(PLOT_TARGET) *.gif *.dat *.txt


plot: build/runSim.o build/system.o 
	$(CXX) $(CXXFLAGS) -o $(PLOT_TARGET) $^
	./$(PLOT_TARGET)
	python3 plot.py

build/runSim.o: runSim.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/system.o: src/system.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@