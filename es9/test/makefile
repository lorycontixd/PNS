CC = g++ -g
CVERSION = -std=c++17
CFLAGS = -Wall -O3
ARMA = -larmadillo
main: main.o
	$(CC) main.cpp -o main ${ARMA} ${CVERSION} -l sqlite3

main.o : main.cpp ../mutations.hpp ../exceptions.hpp ../metrics.hpp ../database.hpp
	$(CC) -c main.cpp -o main.o $(CFLAGS) ${CVERSION}

