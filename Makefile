# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra

# Source files directory
SRCDIR = src

# Source files
SRC = $(wildcard $(SRCDIR)/*.cpp)

# Object files directory
OBJDIR = obj

# Object files
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

# Executable name
TARGET = tracer

all: $(TARGET)
	./tracer > image.ppm

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJDIR) $(TARGET) image.ppm
