CC = g++
CFLAGS = -Wall -O3 --std=c++17
SQLITE = -l sqlite3

main : main.o
	$(CC) main.o -o main ${CFLAGS} ${SQLITE}
	
main.o : main.cpp Ising.hpp random.hpp ../ini_reader.hpp ../functions.hpp
	$(CC) -c main.cpp -o main.o ${CFLAGS} ${SQLITE}

clean :
	chmod +x clean.sh
	./clean.sh
	rm *.o main

cleandirs:
	rm -rf outputs/*
	rm -f final_configs/*
