CC=g++
CFLAGS= -std=c++11

default:
	make all

# link all compiled files and create executable
all: main.o request.o game.o
	$(CC) -o assignment1 main.o request.o game.o $(CFLAGS) -lcurl

# compile main file
main.o: main.cpp
	$(CC) -c main.cpp $(CFLAGS)

# compile request file
request.o: request.cpp
	$(CC) -c request.cpp $(CFLAGS)

# compile game file
game.o: game.cpp
	$(CC) -c game.cpp $(CFLAGS)

clean:
	rm -f main.o request.o game.o assignment1