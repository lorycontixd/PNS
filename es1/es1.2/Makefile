CC = g++
CFLAGS = -Wall -O3 --std=c++17 -lstdc++fs

main : main.o random.o
	$(CC) random.o main.o -o main
main.o : main.cpp ../../functions.h
	$(CC) -c main.cpp -o main.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o main seed.out
