CC = g++
CFLAGS = -Wall -O3 --std=c++17 -lstdc++fs

main : main.o 
	$(CC) main.o -o main
	
main.o : main.cpp metropolis.hpp functions.hpp random.hpp ../datablocking.hpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)


clean :
	rm *.o main seed.out
