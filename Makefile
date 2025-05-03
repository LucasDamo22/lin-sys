# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++20

# Directories
SRC_DIR = src
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/program

# Find all source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Default rule
all: $(TARGET)

# Compile and link source files to create the executable
$(TARGET): $(SRCS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
run: $(TARGET)
	./$(TARGET)

# Clean rule to remove generated files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all clean