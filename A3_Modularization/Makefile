# makefile for the wave1d application

CXX=g++
CXXFLAGS=-O2 -g -std=c++17 -Wall -Wfatal-errors -Wconversion
LDFLAGS=-O2 -g
TARGET=wave1d
OBJS=wave1d.o simulation.o parameters.o io.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)

wave1d.o: wave1d.cpp wave1d.h
	$(CXX) $(CXXFLAGS) -c -o wave1d.o wave1d.cpp

simulation.o: simulation.cpp simulation.h
	$(CXX) $(CXXFLAGS) -c -o simulation.o simulation.cpp

parameters.o: parameters.cpp parameters.h
	$(CXX) $(CXXFLAGS) -c -o parameters.o parameters.cpp

io.o: io.cpp io.h
	$(CXX) $(CXXFLAGS) -c -o io.o io.cpp

run: $(TARGET)
	./$(TARGET) waveparams.txt

clean:
	$(RM) $(OBJS) $(TARGET)

.PHONY: all clean run
