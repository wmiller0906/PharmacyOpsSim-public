# Makefile for PharmacyOpsSim

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude

# Directories
SRC_DIR := src
BIN_DIR := bin

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := $(BIN_DIR)/PharmacyOpsSim

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsodium

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean
