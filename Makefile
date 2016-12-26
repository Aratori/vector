CFLAGS=-std=c++0x

all: Vector

Vector: main.o 
	g++ main.o  -o Vector

main.o: MyVector.cpp MyVector.h main.cpp
	g++ $(CFLAGS) -c main.cpp 

MyVector.o: MyVector.cpp MyVector.h
	g++ $(CFLAGS)  MyVector.cpp MyVector.h

clean:
	rm -rf *.o Vector
