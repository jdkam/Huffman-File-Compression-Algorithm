all: huff

huff: Testdriver.o frequencyCounter.o bitstream.o priorityQueue.h Node.h EmptyDataCollectionException.o huffmanTree.o
	g++ -Wall -o huff Testdriver.o bitstream.o frequencyCounter.o EmptyDataCollectionException.o huffmanTree.o

Testdriver.o: Testdriver.cpp
	g++ -w -c Testdriver.cpp

frequencyCounter.o: frequencyCounter.cpp frequencyCounter.h
	g++ -c frequencyCounter.cpp

bitstream.o: bitstream.h bitstream.cpp
	g++ -c bitstream.cpp

EmptyDataCollectionException.o: EmptyDataCollectionException.h EmptyDataCollectionException.cpp
	g++ -c EmptyDataCollectionException.cpp

huffmanTree.o: huffmanTree.h huffmanTree.cpp 
	g++ -w -c huffmanTree.cpp


clean:
	rm -f huff *.o
