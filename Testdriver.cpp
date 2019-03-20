#include "frequencyCounter.h"
#include "bitstream.h"
#include "priorityQueue.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>

using namespace std;

    void compress();

    void decompress();


int main(int argc, char *argv[])
{

    if (argv[1][0] == '-' && argv[1][1] == 'c')
    {

    //     double charsize = 0;
    //     double codesize = 0;
    //     double totalcompressSize = 0;
    //     huffmanTree myTree;
    //     PriorityQueue<huffmanTree> pq;
    //     freqCounter freqTable;
    //     bitstream mybitstream;
    //     string code;
    //     string *tableBuffer = new string[512];

    //     ifstream in(argv[2], ios::binary);

    //     //mybitstream.readIn(argv[2]); //reads in a file in a block
    // if(!in.is_open()){
    //     cout << "There was an error opening the file" << endl;
    //     return 1;
    // }

    // in.seekg(0, ios::end);
    // ifstream::pos_type size = in.tellg();
    // cout << argv[2] << " -> " << size << " bytes" << endl;
    // if (size == 0) {
    //     ofstream of(argv[2]);
    //     cout << argv[3] << " -> 0 bytes" << endl;
    //     return 0;
    // }

    // in.clear();
    // in.seekg(0,ios::beg);
    //     int length = mybitstream.getBufferLength();
    //     //cout << "\nBuffer length: " << length << endl;
    //     char *mybuffer = new char[length];
    //     mybuffer = mybitstream.getBuffer();

    //     freqCounter *newTable = freqTable.generateTable(length, mybuffer);
    //     newTable[256].setFreq(1);
    //     int tableLength = freqTable.getUniqueLength();

    //     freqCounter f(in);

    //     unsigned int numberChars = 0;

    //     for (unsigned short i = 0; i < 257; i++)
    //     {
    //         if (newTable[i].getFreq() != 0)
    //         {
    //             unsigned fq = f.getFreqOfChar(i);
    //             if (fq == 0)
    //                 continue;
    //             huffmanTree huff(fq, i);
    //             pq.enqueue(huff);
    //             //count the number of chars that appear for later
    //             numberChars++;
    //         }
    //     }

    //     numberChars--;

    //     huffmanTree leTree = pq.peek();
    //     pq.dequeue();
    //     while (!pq.isEmpty())
    //     {
    //         huffmanTree huff0 = pq.peek();
    //         pq.dequeue();
    //         huffmanTree huff1(leTree, huff0);
    //         pq.enqueue(huff1);
    //         leTree = pq.peek();
    //         pq.dequeue();
    //     }

    //     //get first letter, then find corresponding index of codeTable and print
    //     string *codeTable = new string[257];

    //     leTree.makeCodeTable(codeTable);
    //     //cout << "test********************\n";

    //     ofstream out(argv[3], ios::binary);
    //     if (!out.is_open())
    //     {
    //         return -1;
    //     }

    //     char *numOfCharsPtr = (char *)&numberChars;

    //     out.write(numOfCharsPtr, sizeof(unsigned));

    //     char *buffer = new char[numberChars];
    //     unsigned *uiBuffer = new unsigned[numberChars * 4];
    //     int i = 0;

    //     for (unsigned short c = 0; c < 256; c++)
    //     {
    //         if (codeTable[c].empty())
    //             continue;
    //         buffer[i] = (unsigned char)c;
    //         uiBuffer[i] = f.getFreqOfChar(c);
    //         // cout << codeTable[c] << endl;
    //         i++;
    //     }
    //     out.write(buffer, sizeof(unsigned char) * numberChars);
    //     out.write((char *)uiBuffer, sizeof(unsigned) * numberChars);

    //     delete[] buffer;
    //     delete[] uiBuffer;

    //     bitstream bs(codeTable);
    //     //ifstream in(argv[2], ios::binary);
    //     in.clear();
    //     in.seekg(0, ios::beg);
    //     bool done = false;
    //     while (!done)
    //     {

    //         char *buff = bs.getNext(in, &done);
    //         out.write(buff, 1);
    //     }
    //     delete[] codeTable;

    //     cout << argv[3] << " -> " << out.tellp() << " bytes" << endl;
    //     if (length < out.tellp())
    //         cout << "*** Size of compressed file > size of source file ***" << endl;
        
    //     in.clear();
    //     out.close();
    //     in.close();
    //     //read file back
    //     return 0;
    //     cout << "test**************";

    ifstream in(argv[2],ios::binary);//opening file

    if(!in.is_open()){
        cout << "There was an error opening the file" << endl;
        return 1;
    }

    in.seekg(0, ios::end);
    ifstream::pos_type size = in.tellg();
    cout << argv[2] << " -> " << size << " bytes" << endl;
    if (size == 0) {
        ofstream of(argv[2]);
        cout << argv[3] << " -> 0 bytes" << endl;
        return 0;
    }

    in.clear();
    in.seekg(0,ios::beg);

    //make frequancy table
    freqCounter fq(in);
    PriorityQueue<huffmanTree> q;

    //turn frequencies into weighted huffman trees, and put in priority queue
    unsigned int numOfChars = 0;
    for(unsigned short c = 0; c < 257; c++){
        unsigned f = fq.getFreqOfChar(c);
        if(f == 0)continue;
        huffmanTree huff(f,c);
        q.enqueue(huff);
        //count the number of chars that appear for later
        numOfChars++;
    }
    numOfChars--;

    //add trees together, and place back into queue until the queue is empty
    huffmanTree daTree = q.peek();
    q.dequeue();
    while(!q.isEmpty()){
        huffmanTree huff2 = q.peek();
        q.dequeue();
        huffmanTree huff3(daTree,huff2);
        q.enqueue(huff3);
        daTree = q.peek();
        q.dequeue();
    }

    //get codeTable from the huffman tree
    string* codeTable = new string[257];
    daTree.makeCodeTable(codeTable);

    //encoding:
    //encode the number of characters, all of the characters and then all of their frequencies
    ofstream out(argv[3], ios::binary);
    if(!out.is_open()){
        cout << "something went wrong when trying to open huff file" << endl;
        return 1;
    }

    char* numOfCharsPtr = (char*)&numOfChars;
    //write the number of chars
    out.write(numOfCharsPtr,sizeof(unsigned));
    //write all of the characters that are
    char* buffer = new char[numOfChars];
    unsigned* uiBuffer = new unsigned[numOfChars*4];
    int i = 0;
    //we don't write the freq of the null char because the decoder will know its 1
    for(unsigned short c = 0; c < 256; c++){
        if(codeTable[c].empty())continue;
        buffer[i] = (unsigned char)c;
        uiBuffer[i] = fq.getFreqOfChar(c);
        i++;
    }

    out.write(buffer,sizeof(unsigned char)*numOfChars);
    out.write((char*)uiBuffer,sizeof(unsigned)*numOfChars);

    delete[] buffer;
    delete[] uiBuffer;

    bitstream bs(codeTable);

    in.clear();
    in.seekg(0,ios::beg);
    bool done = false;
    while(!done){
        char* buff = bs.getNext(in,&done);
        out.write(buff,1);
    }
    delete[] codeTable;

    cout << argv[3] << " -> " << out.tellp() << " bytes" << endl;
    if(size < out.tellp()) cout << "*** Size of compressed file > size of source file ***" << endl;
    out.close();
    in.close();
    //read file back
    return 0;

    }
    else if (argv[1][0] == '-' && argv[1][1] == 'd')
    {
        //decompression
        ifstream in(argv[2], ios::binary);

        if (!in)
            return 1;

        in.seekg(0, ios::end); //read the file
        if (in.tellg() == 0)
        {
            ofstream of(argv[3]);
            return 0;
        }
        in.clear();
        in.seekg(0, ios::beg);

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
        huffmanTree daTree = q.peek();
        q.dequeue();
        while (!q.isEmpty())
        {
            huffmanTree huff2 = q.peek();
            q.dequeue();
            huffmanTree huff3(daTree, huff2);
            q.enqueue(huff3);
            daTree = q.peek();
            q.dequeue();
        }
        //std::cout << daTree.returnRoot()->getVal()->getleft() << endl;

        string *codeTable = new string[257];
        daTree.makeCodeTable(codeTable); //adding everything to the table to push to the file later in order
                                         //clearing the allocated space
        delete[] buffer;
        delete[] freqs;
        delete[] codeTable;

        ofstream out(argv[3], ios::binary);

        bool done = false;
        char c = daTree.getC(in, &done);
        while (!done)
        {
            out.write(&c, sizeof(char));
            c = daTree.getC(in, &done);
        }
        out.close(); //close the file and done!

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