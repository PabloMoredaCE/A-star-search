CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

TARGET = astar

# First look for .cpp files inside src/
SRC = $(wildcard src/*.cpp)

# If there is no src/ folder, use .cpp files in the current directory
ifeq ($(strip $(SRC)),)
SRC = $(wildcard *.cpp)
endif

OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean