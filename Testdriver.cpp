#include "frequencyCounter.h"
#include "bitstream.h"
#include <iostream>

int main()
{
    using namespace std;
    int freq = 5;
    char mychar = 'f';
    freqCounter freqTable;

    freqTable.setFreq(&freq);
    freqTable.setChar(&mychar);

    cout << freqTable.getChar() << ": " << freqTable.getFreq() << endl;

    bitstream mybitstream;

    mybitstream.readIn(); //reads in a file in a block

    int length = mybitstream.getBufferLength();
    cout << "\nBuffer length: " << length << endl;
    char * mybuffer = new char[length];

    mybuffer = mybitstream.getBuffer();
    cout << "PRINTING BUFFER: \n";
    for(int i=0; i<length; i++)
    {
    cout << mybuffer[i];

    }
    freqTable.generateTable(length, mybuffer);

    cout << "\n********END PROGRAM********" << endl;


    return (0);

}