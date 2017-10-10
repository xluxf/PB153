CXX=g++-7
CXXFLAGS=-std=c++14 -Wall -O2 -g -Ibricks
LDFLAGS=
SOURCES=ex1.cpp hw1.cpp ex2.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ex1 hw1 ex2


ex1:ex1.cpp
	$(CXX) $(CXXFLAGS) -o ex1 ex1.cpp

hw1:hw1.cpp
	$(CXX) $(CXXFLAGS) -o hw1 hw1.cpp

ex2:ex2.cpp
	$(CXX) $(CXXFLAGS) -o ex2 ex2.cpp
