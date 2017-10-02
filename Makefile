CC=g++
CFLAGS=-std=c++11 -Wall 
LDFLAGS=
SOURCES=ex1.cpp hw1.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ex1 hw1


ex1:ex1.cpp
	$(CC) $(CFLAGS) -o ex1 ex1.cpp

hw1:hw1.cpp
	$(CC) $(CFLAGS) -o hw1 hw1.cpp
