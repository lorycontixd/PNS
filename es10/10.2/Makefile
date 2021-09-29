CC = mpic++
CFLAGS = -O3 --std=c++17 
SILENCE_MAC = -Wno-unused-variable -Wno-unused-private-field -Wreturn-typec -Wreturn-type
SILENCE_WINDOWS = -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-unused-variable -Wno-unused-result -Wno-return-local-addr
INVOCATION = -v
SQLITE = -l sqlite3

main : main.o
	$(CC) main.o -o  main ${CFLAGS} ${SQLITE} ${SILENCE_WINDOWS}
	
main.o : main.cpp mutations.hpp citygen.hpp settings.hpp genetic.hpp population.hpp individual.hpp metrics.hpp random.hpp exceptions.hpp ../../ini_reader.hpp ../../functions.hpp ../../logger.hpp
	$(CC) -c main.cpp -o main.o ${CFLAGS} ${SQLITE} ${NO_PRIVATE} ${NO_VARIABLE}

run:
	mpirun -n 6 ./main config.ini
	
clean :
	rm *.o main seed.out

cleancircle:
	rm *.o main seed.out
	rm -rf outputs/circle/

cleansquare:
	rm *.o main seed.out
	rm -rf outputs/square/

cleanall:
	rm *.o main seed.out
	rm -rf outputs/*
