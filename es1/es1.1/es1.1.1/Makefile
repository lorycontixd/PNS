CC = g++
CFLAGS = -Wall -O3 --std=c++17
FILESYSTEM = -lstdc++fs

main : main.o 
	$(CC) main.o -o main ${FILESYSTEM}
main.o : main.cpp random.hpp ../../../functions.hpp ../../../ini_reader.hpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.hpp
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main seed.out
