LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
 
%.o : %.cpp
	g++ -Wall -c $< ${INCS}

qmc1d: qmc1d.o
	g++ -O3 -Wall -o $@ $^ ${LIBS}

qmc1d_bumps: qmc1d_bumps.o
	g++ -O3 -Wall -o $@ $^ ${LIBS}

clean:
	rm *.o qmc1d
	rm -rf outputs/*

cleanpigs:
	rm -rf outputs/PIGS/*

cleanpimc:
	rm -rf outputs/PIMC/*
