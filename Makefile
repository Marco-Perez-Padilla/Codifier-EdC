CXX = g++
CXXFLAGS = -std=c++23 -Wall

EXCLUDED_FILE = test.cc

SOURCES = $(filter-out $(EXCLUDED_FILE), $(wildcard *.cc))
OBJ = $(SOURCES:.cc=.o)

EXECUTABLE = Codifier

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXECUTABLE)
