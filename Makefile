CXX=g++-7
CXXFLAGS=-std=c++14 -Wall -O2 -g -Ibricks
LDFLAGS=
SOURCES=ex1.cpp hw1.cpp ex2.cpp ex3.cpp bench.cpp test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ex1 hw1 ex2 ex3 bench test


ex1:ex1.cpp
	$(CXX) $(CXXFLAGS) -o ex1 ex1.cpp

hw1:hw1.cpp
	$(CXX) $(CXXFLAGS) -o hw1 hw1.cpp

ex2:ex2.cpp
	$(CXX) $(CXXFLAGS) -o ex2 ex2.cpp

ex3:ex3.cpp
	$(CXX) $(CXXFLAGS) -o ex3 ex3.cpp

bench:bench.cpp
	$(CXX) $(CXXFLAGS) -o bench bench.cpp

test:test.cpp
	$(CXX) $(CXXFLAGS) -o test test.cpp
