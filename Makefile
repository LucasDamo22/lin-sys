CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++20

SRC_DIR = src
BIN_DIR = bin
CASE_DIR = cases

TARGET = $(BIN_DIR)/program

SRCS = $(wildcard $(SRC_DIR)/*.cpp)

all: $(TARGET)

$(TARGET): $(SRCS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: $(TARGET)
	./$(TARGET) $(CASE_DIR)/caso10.txt 300000; \
	./$(TARGET) $(CASE_DIR)/caso20.txt 300000; \
	./$(TARGET) $(CASE_DIR)/caso30.txt 300000; \
	./$(TARGET) $(CASE_DIR)/caso50.txt 300000; \
	./$(TARGET) $(CASE_DIR)/caso100.txt 300000; \
	./$(TARGET) $(CASE_DIR)/caso150.txt 300000; \
	./$(TARGET) $(CASE_DIR)/caso200.txt 300000;
	
clean:
	rm -rf $(BIN_DIR)
