#include "frequencyCounter.h"
#include "bitstream.h"
#include "priorityQueue.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>

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

    PriorityQueue<huffmanTree> pq;
    //char amountOfCharacters = 0;
    for (int i = 0; i < 256; i++)
    {

        if (newTable[i].getFreq() != 0)
        {
            //cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
            huffmanTree huff = huffmanTree(newTable[i].getFreq(), newTable[i].getChar());

           // cout <<  huff.getData() << " : " <<  myNode->getFreq() << endl;

            pq.enqueue(huff);
           //amountOfCharacters++;
        }
    }

    huffmanTree leTree = pq.peek();
    pq.dequeue();
    while (!pq.isEmpty())
    {
        huffmanTree huff0 = pq.peek();
        pq.dequeue();
        huffmanTree huff1(leTree, huff0);
        pq.enqueue(huff1);
        leTree = pq.peek();
        pq.dequeue();
    }


    string codeTable[257];
    leTree.makeCodeTable(codeTable);

    
    string code;
    for (int i = 0; i < length; i++)
    {
        //get first letter, then find corresponding index of codeTable and print

        int k = mybuffer[i];
        //cout << "buffer: " << mybuffer[i];
        //char thisChar = newTable[i].getChar();
        string thisString = codeTable[k];
        code += thisString;
        newTable[i].setCodeWord(thisString);
        //cout << " " << newTable[i].getCodeWord() << endl;
    }


    //print the huffman code in order of ascii appeareance
    cout << "HUFFCODE: " << code << endl;
    cout << "Compressed size -> " << code.size() << " bytes\n";
    cout << "original file size -> " << mybitstream.getBufferLength()*8 << " bytes\n";
    // need to print code to file (bitstream)

    string tableBuffer;

//transfer frequency table to a printable string
    for(int i=0; i<256; i++){

        if(newTable[i].getFreq() != 0){
            
            cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
            cout << tableBuffer;
        }
    }

    //cout << tableBuffer << endl;


    mybitstream.writeOut(code);

    // need to decode
    // need to finish commands line argc
    // need to organize test driver

    return (0);
}