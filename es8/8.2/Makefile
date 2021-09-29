CC = g++
CFLAGS = -Wall -O3 --std=c++17

main: main.o 
	$(CC) main.cpp -o main ${CFLAGS}
main.o: main.cpp random.hpp metropolis.hpp datablocking.hpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)	

clean :
	rm -rf *.o main main_isto seed.out outputs/automation/* outputs/single/*

cleanauto:
	rm -rf *.o outputs/automation/*

cleansingle:
	rm -rf *.o outputs/single/*