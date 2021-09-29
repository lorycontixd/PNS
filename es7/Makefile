CC = g++
CFLAGS = -Wall -O3 --std=c++17 -lstdc++fs
NO_VARIABLE = -Wno-unused-variable 
NO_PRIVATE = -Wno-unused-private-field

main: main.o
	$(CC) main.o -o main ${CFLAGS}

main.o : main.cpp NVT.hpp random.hpp ../datablocking.hpp ../ini_reader.hpp ../functions.hpp
	$(CC) -c main.cpp -o main.o  ${NO_PRIVATE} ${NO_VARIABLE}

clean :
	rm *.o Monte_Carlo_NVT
