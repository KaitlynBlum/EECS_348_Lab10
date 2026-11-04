
# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Executable name
TARGET = matrix

# Source file
SOURCE = main.cpp

# Default rule
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Remove executable
clean:
	rm -f $(TARGET)
