CXX = g++
CXXFLAGS = -Wall -Werror -std=c++11
LDFLAGS = -lgtest -lgtest_main -pthread -lopenssl
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = tests

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/*/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Test source files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(TEST_SOURCES))

# Executables
EXECUTABLE = $(BIN_DIR)/client
TEST_EXECUTABLE = $(BIN_DIR)/run_tests

.PHONY: all clean test

# Default rule
all: $(EXECUTABLE)

# Build the executable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Build test runner
$(TEST_EXECUTABLE): $(TEST_OBJECTS) $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(TEST_OBJECTS) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile test object files
$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run tests
test: $(TEST_EXECUTABLE)
	$(TEST_EXECUTABLE)

# Clean up
clean:
	rm -rf $(BUILD_DIR)/*.o $(EXECUTABLE) $(TEST_EXECUTABLE) $(BIN_DIR)
