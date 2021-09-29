CC = g++
CFLAGS = -Wall -O3 --std=c++17 -lstdc++fs
BOOST = -I /usr/local/Cellar/boost/1.76.0
NO_VARIABLE = -Wno-unused-variable 
NO_PRIVATE = -Wno-unused-private-field
INVOCATION = -v

main : main.o
	$(CC) main.o -o main
	
main.o : main.cpp random.hpp ../../ini_reader.hpp ../../functions.hpp ../../datablocking.hpp
	$(CC) -c main.cpp -o main.o ${CFLAGS} ${NO_PRIVATE} ${NO_VARIABLE}

clean :
	rm *.o main seed.out