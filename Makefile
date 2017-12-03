CXX=g++-7
CXXFLAGS=-std=c++14 -Wall -O2 -g -Ibricks
LDFLAGS=
SOURCES=ex1.cpp hw1.cpp ex2.cpp ex3.cpp ex7.cpp bench.cpp test.cpp bfs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ex1 hw1 ex2 ex3 bench test bfs


ex1:ex1.cpp
	$(CXX) $(CXXFLAGS) -o ex1 ex1.cpp

hw1:hw1.cpp
	$(CXX) $(CXXFLAGS) -o hw1 hw1.cpp

hw3:hw3.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o hw3 hw3.cpp

hw5:hw5.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -o hw5 hw5.cpp

ex2:ex2.cpp
	$(CXX) $(CXXFLAGS) -o ex2 ex2.cpp

ex3:ex3.cpp
	$(CXX) $(CXXFLAGS) -o ex3 ex3.cpp

ex7:ex7.cpp
	$(CXX) $(CXXFLAGS) -o ex7 ex7.cpp

bench:bench.cpp
	$(CXX) $(CXXFLAGS) -o bench bench.cpp

test:test.cpp
	$(CXX) $(CXXFLAGS) -o test test.cpp

bfs:bfs.cpp
	$(CXX) $(CXXFLAGS) -o bfs bfs.cpp

hw4_check: hw4_check.cpp hw4.cpp
	$(CXX) $(CXXFLAGS) -o hw4_check hw4_check.cpp
	./hw4_check

hw4: hw4.cpp hw4.hpp
	$(CXX) $(CXXFLAGS) -O2 -o hw4 hw4.cpp
	rm -f benchmark.log
	./hw4 category:charset > bench.gp
	gnuplot < bench.gp > hw4_bench.pdf