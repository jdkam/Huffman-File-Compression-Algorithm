all: test

test: Testdriver.o frequencyCounter.o bitstream.o
	g++ -Wall -o test Testdriver.o bitstream.o frequencyCounter.o

Testdriver.o: Testdriver.cpp
	g++ -c Testdriver.cpp

frequencyCounter.o: frequencyCounter.cpp frequencyCounter.h
	g++ -c frequencyCounter.cpp

bitstream.o: bitstream.h bitstream.cpp
	g++ -c bitstream.cpp


clean:
	rm -f sim *.o
