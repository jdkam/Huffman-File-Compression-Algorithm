#include "frequencyCounter.h"
#include "bitstream.h"
#include <iostream>

int main()
{
    using namespace std;
    int freq = 5;
    char mychar = 'f';
    freqCounter freqTable;

    freqTable.setFreq(freq);
    freqTable.setChar(mychar);

    cout << freqTable.getChar() << ": " << freqTable.getFreq() << endl;

    bitstream mybitstream;

    mybitstream.readIn(); //reads in a file in a block

    int length = mybitstream.getBufferLength();
    cout << "\nBuffer length: " << length << endl;
    char * mybuffer = new char[length];

    mybuffer = mybitstream.getBuffer();
    //cout << "PRINTING BUFFER: \n";
    //for(int i=0; i<length; i++)
    //{
   // cout << mybuffer[i];

   // }
    freqCounter * newTable = freqTable.generateTable(length, mybuffer);

    //freqCounter *newTable = freqTable.getTable();
    //freqCounter* newTable = new freqCounter[255];

    //copyover array of objects


    for(int i=0; i <length; i++)
    {
        //newTable[i] = freqTable.getTable(i);

    }

    for(int i=0; i<255; i++)
    {
        if(newTable[i].getFreq() != 0){
        cout << newTable[i].getChar() << " : ";
        cout << newTable[i].getFreq() << endl;
       }
    }

    cout << "\n********END PROGRAM********" << endl;


    return (0);

}