#include "frequencyCounter.h"
#include "bitstream.h"
#include "priorityQueue.h"
#include "huffmanTree.h"
#include <iostream>

using namespace std;
PriorityQueue<freqCounter> myQueue;

int main(int argc, char *argv[])
{
    huffmanTree myTree;
    freqCounter freqTable;

    bitstream mybitstream;

    mybitstream.readIn(argv[1]); //reads in a file in a block

    int length = mybitstream.getBufferLength();
    cout << "\nBuffer length: " << length << endl;
    char *mybuffer = new char[length];

    mybuffer = mybitstream.getBuffer();

    freqCounter *newTable = freqTable.generateTable(length, mybuffer);

    int tableLength = freqTable.getUniqueLength();


    myTree.buildTree(newTable, tableLength);


    
    return (0);
}