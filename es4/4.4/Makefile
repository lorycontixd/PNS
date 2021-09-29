CC = g++
CFLAGS = -Wall -O3 --std=c++17

main : main.o
	$(CC) main.o -o main $(CFLAGS)

main.o: main.cpp ../inc/random.hpp datablocking.hpp NVE.hpp
	$(CC) -c main.cpp -o main.o $(CFLAGS)
clean: 
	chmod +x clean.sh
	./clean.sh
	rm *.o
esegui:
	./main
