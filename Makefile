flags = -g -pthread -std=c++11
objects = main.o Physics.o Point.o Object.o Rectangle.o Polygon.o easygl.o graphics.o

all: $(objects)
	g++ $(flags) $(objects) -lX11 -o physics

main.o: main.cpp
	g++ $(flags) -c main.cpp

Physics.o: Physics.cpp
	g++ $(flags) -c Physics.cpp

Point.o: Point.cpp
	g++ $(flags) -c Point.cpp

Object.o: Object.cpp
	g++ $(flags) -c Object.cpp

Rectangle.o: Rectangle.cpp
	g++ $(flags) -c Rectangle.cpp

Polygon.o: Polygon.cpp
	g++ $(flags) -c Polygon.cpp

graphics.o: graphics.cpp
	g++ $(flags) -DX11 -c graphics.cpp

easygl.o: easygl.cpp
	g++ $(flags) -DX11 -c easygl.cpp

clean:
	rm -rf *.o physics
