CC = g++
CFLAGS = -O3 --std=c++17 
ARMA = -larmadillo
SILENCE_MAC = -Wno-unused-variable -Wno-unused-private-field -Wreturn-typec -Wreturn-type
SILENCE_WINDOWS = -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-unused-result -Wno-return-local-addr
INVOCATION = -v
SQLITE = -l sqlite3

main : main.o
	$(CC) main.o -o  main  ${SQLITE} ${SILENCE_WINDOWS}
	
main.o : main.cpp mutations.hpp database.hpp citygen.hpp settings.hpp genetic.hpp population.hpp individual.hpp metrics.hpp random.hpp exceptions.hpp ../../ini_reader.hpp ../../functions.hpp ../../logger.hpp
	$(CC) -c main.cpp -o main.o ${CFLAGS} ${NO_PRIVATE} ${NO_VARIABLE}

run:
	./main config.ini
clean :
	rm *.o main seed.out
