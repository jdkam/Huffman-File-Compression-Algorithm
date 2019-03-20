#include "frequencyCounter.h"
#include "bitstream.h"
#include "priorityQueue.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>


using namespace std;

int main(int argc, char *argv[])
{

    if (argv[1][0] == '-' && argv[1][1] == 'c')
    {

        double charsize = 0;
        double codesize = 0;
        double totalcompressSize = 0;
        huffmanTree myTree;
        PriorityQueue<huffmanTree> pq;
        freqCounter freqTable;
        bitstream mybitstream;
        string code;
        string *tableBuffer = new string[512];

        mybitstream.readIn(argv[2]); //reads in a file in a block
        int length = mybitstream.getBufferLength();
        // cout << "\nBuffer length: " << length << endl;
        char *mybuffer = new char[length];
        mybuffer = mybitstream.getBuffer();

        freqCounter *newTable = freqTable.generateTable(length, mybuffer);
        newTable[256].setFreq(1);
        int tableLength = freqTable.getUniqueLength();

        unsigned int numberChars = 0;
        for (unsigned short i = 0; i < 256; i++)
        {
            if (newTable[i].getFreq() != 0)
            {
                //cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
                huffmanTree huff = huffmanTree(newTable[i].getFreq(), newTable[i].getChar());
                pq.enqueue(huff);
                numberChars++;
            }
        }
        numberChars--;

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

        //get first letter, then find corresponding index of codeTable and print
        string *codeTable = new string[257];

        leTree.makeCodeTable(codeTable);
        //cout << "test********************\n";

        ofstream out(argv[3], ios::binary);
        if (!out.is_open())
        {
            return -1;
        }

        char *numOfCharsPtr = (char *)&numberChars;

        out.write(numOfCharsPtr, sizeof(unsigned));

        char *buffer = new char[numberChars];
        unsigned *uiBuffer = new unsigned[numberChars * 4];
        int i = 0;

        for (unsigned short c = 0; c < 256; c++)
        {
            if (codeTable[c].empty())
                continue;
            buffer[i] = (unsigned char)c;
            uiBuffer[i] = newTable[c].getFreq();
            // cout << codeTable[c] << endl;
            i++;
        }
        out.write(buffer, sizeof(unsigned char) * numberChars);
        out.write((char *)uiBuffer, sizeof(unsigned) * numberChars);

        delete[] buffer;
        delete[] uiBuffer;

        bitstream bs(codeTable);
        ifstream in(argv[2], ios::binary);
        in.clear();
        in.seekg(0, ios::beg);
        bool done = false;
        while (!done)
        {

            char *buff = bs.getNext(in, &done);
            out.write(buff, 1);
        }
        delete[] codeTable;

        cout << argv[3] << " -> " << out.tellp() << " bytes" << endl;
        if (length < out.tellp())
            cout << "*** Size of compressed file > size of source file ***" << endl;
        out.close();
        in.close();
        //read file back
        return 0;
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'd')
    {
        //decompression
        ifstream in(argv[2], ios::binary);
        unsigned n;
        in.read((char *)&n, sizeof(unsigned));
        unsigned int num = n;
        unsigned char *buffer = new unsigned char[num];
        in.read((char *)buffer, sizeof(char) * num);

        unsigned *freqs = new unsigned[num];
        in.read((char *)freqs, sizeof(unsigned) * num);

        PriorityQueue<huffmanTree> q; //create a new priority queue to store the characters in order
        for (int i = 0; i < num; i++)
        {
            huffmanTree huff(freqs[i], (unsigned short)buffer[i]);
            q.enqueue(huff);
        }
        huffmanTree huffhuff(1, 256);
        q.enqueue(huffhuff);

        //add trees together, and place back into queue until the queue is empty
        huffmanTree tree = q.peek();
        q.dequeue();
        while (!q.isEmpty())
        {
            huffmanTree huff4 = q.peek();
            q.dequeue();
            huffmanTree huff2(tree, huff4);
            q.enqueue(huff2);
            tree = q.peek();
            q.dequeue();
        }

        string *codeTable = new string[257];
        tree.makeCodeTable(codeTable); 
                                            
        delete[] buffer;
        delete[] freqs;
        delete[] codeTable;

        ofstream out(argv[3], ios::binary);

        bool done = false;
        char c = tree.getC(in, &done); //

        while (!done)
        {
            out.write(&c, sizeof(char));
            c = tree.getC(in, &done);
        }
        out.close(); 

        return 0;
    }
    else
    {
        cerr << "invalid command" << endl;
        return -1;
    }

    // need to decode
    // need to finish commands line argc
    // need to organize test driver

    return (0);
}