#include "frequencyCounter.h"
#include "bitstream.h"
#include "priorityQueue.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>
#include <map>

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
        int tableLength = freqTable.getUniqueLength();

        for (int i = 0; i < 256; i++)
        {
            if (newTable[i].getFreq() != 0)
            {
                //cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
                huffmanTree huff = huffmanTree(newTable[i].getFreq(), newTable[i].getChar());
                pq.enqueue(huff);
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

        //get first letter, then find corresponding index of codeTable and print
        string codeTable[length];
        leTree.makeCodeTable(codeTable);
        for (int i = 0; i < length; i++)
        {

            int k = mybuffer[i];
            //cout << "buffer: " << mybuffer[i];
            //char thisChar = newTable[i].getChar();
            string thisString = codeTable[k];
            code += thisString;
            newTable[k].setCodeWord(thisString);
            //cout << " " << newTable[i].getCodeWord() << endl;
        }

        //cout << "HUFFCODE: " << code << endl;
        //cout << "Compressed size -> " << code.size()/8 << " bytes\n";
        cout << "original file size -> " << mybitstream.getBufferLength() * 8 << " bytes\n";
        double originalSize = (mybitstream.getBufferLength() * 8);

        //transfer frequency table to a printable string
        int j = 0;
        for (int i = 0; i < 256; i++)
        {
            char c;
            int f;
            if (newTable[i].getFreq() != 0)
            {
                c = newTable[i].getChar();
                tableBuffer[j] += c;
                tableBuffer[j] += codeTable[i];
                charsize++;
                codesize += codeTable[i].size();
                //cout << "total char size: " << charsize << "bytes" << endl;
                //cout << "current code size: " << codeTable[i].size() << "bits" << endl;

                //cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
                //cout << tableBuffer;
                j++;
            }
        }
        //cout << "total code size: " << codesize << endl;
        //cout << "total char size" << charsize << endl;
        codesize = double(code.size() / 8) + double(codesize / 8); //convert bytes
        totalcompressSize = codesize + charsize;
        //cout << "total code size: " << codesize << " bytes" << endl;

        //cout << tableBuffer[1][1] << endl;

        mybitstream.writeOut(code, tableBuffer, tableLength, argv[3]);
        cout << "Compressed size -> " << totalcompressSize << " bytes\n";
        if (totalcompressSize > originalSize)
        {
            cout << "*** size of compressed file > size of source file ***\n";
        }
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'd')
    {
        //decompression

        std::ifstream is(argv[2], std::ifstream::binary);
        char chararr[256] = {};
        string str[256] = {};

        if (is)
        {
            string huffcode;
            getline(is, huffcode);

            cout << huffcode << endl;

            int numofchar = 0;
            while (!(is.eof()))
            {
                int i = 1;
                string mapLine;
                getline(is, mapLine);
                char c;
                c = mapLine[0];

                string zerosOnes = "";
                while (mapLine[i] != '\0')
                {

                    zerosOnes += mapLine[i];
                    i++;
                }
                str[numofchar] = zerosOnes;

                chararr[numofchar] = c;
                cout << "The first character is: " << c << endl;
                cout << "The corresponding numbers are: " << zerosOnes << endl
                     << endl;
                numofchar++;
            }

            // cout << "printing array" << endl;
            // for (int i = 0; i < 256; i++)
            // {
            //     if (str[i] != "")
            //     {
            //         cout << "char " << chararr[i];
            //         cout << " " << str[i] << endl;
            //     }
            // }
        }
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