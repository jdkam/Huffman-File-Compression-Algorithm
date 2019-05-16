/*  Testdriver.cpp
*   Desc: Main interface towards compression and decompression
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/

#include "frequencyCounter.h"
#include "bitstream.h"
#include "priorityQueue.h"
#include "huffmanTree.h"
#include <iostream>
#include <string>

using namespace std;

void compress(int argc, char *argv[]);

void decompress(int argc, char *argv[]);

void decompress(int argc, char *argv[])
{
    //  Open File
    ifstream input(argv[2], ios::binary);

    //  If input did not open
    if (!input)
    {
        return;
    }

    //  Read the file here
    input.seekg(0, ios::end); 
    if (input.tellg() == 0)
    {
        ofstream of(argv[3]);
        return;
    }
    input.clear();
    input.seekg(0, ios::beg); 


    unsigned n;
    input.read((char *)&n, sizeof(unsigned));
    unsigned int num = n;

    //  Creating one-to-one arrays
    unsigned char *buffer = new unsigned char[num];
    input.read((char *)buffer, sizeof(char) * num);
    unsigned *freqs = new unsigned[num];
    input.read((char *)freqs, sizeof(unsigned) * num);
      

    //  Creating priority queue for storing characters in sorted fashion
    PriorityQueue<huffmanTree> pq; 
    for (int i = 0; i < num; i++)
    {
        huffmanTree huff(freqs[i], (unsigned short)buffer[i]);
        pq.enqueue(huff);
    }
    huffmanTree huffhuff(1, 256);
    pq.enqueue(huffhuff);


    //  Linkage of trees for putting back into queue
    huffmanTree hufftree = pq.peek();
    pq.dequeue();
    while (!pq.isEmpty())
    {
        huffmanTree huff2 = pq.peek();
        pq.dequeue();
        huffmanTree huff3(hufftree, huff2);
        pq.enqueue(huff3);
        hufftree = pq.peek();
        pq.dequeue();
    }
   
    //  Create the code table from huffmanTree class
    string *codeTable = new string[257];
    hufftree.makeCodeTable(codeTable); 

    //  Delete no longer needed datas
    delete[] buffer;
    delete[] freqs;
    delete[] codeTable;

    ofstream outfile(argv[3], ios::binary);

    //  Writes decompressed data onto new file
    bool finished = false;
    char c = hufftree.getC(input, &finished);
    while (!finished)
    {
        outfile.write(&c, sizeof(char));
        c = hufftree.getC(input, &finished);
    }
    outfile.close(); 
}

void compress(int argc, char *argv[])
{
    //  Open the file
    ifstream input(argv[2], ios::binary);

    //  If file didnt open
    if (!input.is_open())
    {
        cerr << "Error opening file" << endl;
        return;
    }

    //  Find the amount of bytes in file
    input.seekg(0, ios::end);
    ifstream::pos_type size = input.tellg();
    cout << argv[2] << " -> " << size << " bytes" << endl;
    if (size == 0)
    {
        ofstream of(argv[2]);
        cout << argv[3] << " -> 0 bytes" << endl;
        return;
    }
    input.clear();
    input.seekg(0, ios::beg);


    //  Creation of frequency table and priority queue
    freqCounter fq(input);
    PriorityQueue<huffmanTree> pq;

    //  Use frequency data for huffmanTree creation for priority queue
    unsigned int numOfChars = -1;
    for (unsigned short c = 0; c < 257; c++)
    {
        unsigned f = fq.getFreq(c);
        if (f == 0)
            continue;
        huffmanTree huff(f, c);
        pq.enqueue(huff);
        
        //  The amount of ascii characters that pop up
        numOfChars++;
    }
    

    //  Linkage of nodes in pq for proper tree creation
    huffmanTree hufftree = pq.peek();
    pq.dequeue();
    while (!pq.isEmpty())
    {
        huffmanTree huff2 = pq.peek();
        pq.dequeue();
        huffmanTree huff3(hufftree, huff2);
        pq.enqueue(huff3);
        hufftree = pq.peek();
        pq.dequeue();
    }

    //  Obtaining the huffman tree codes
    string *codeTable = new string[257];
    hufftree.makeCodeTable(codeTable);

    //  Encode the ascii characters with freq > 0, all characters and all frequencies, respectively
    ofstream outfile(argv[3], ios::binary);
    if (!outfile.is_open())
    {
        cout << "something went wrong when trying to open huff file" << endl;
        return;
    }

    //  Writing the ascii characters with freq > 0
    char* numOfCharsPtr = (char *)&numOfChars;
    outfile.write(numOfCharsPtr, sizeof(unsigned));

    //  Arrays used for encoding
    char* buffer = new char[numOfChars];
    unsigned* fbuffer = new unsigned[numOfChars * 4];

    //  Giving the arrays their appropriate information for output into file
    int i = 0;
    for (unsigned short c = 0; c < 256; c++)
    {
        if (codeTable[c].empty())
            continue;
        buffer[i] = (unsigned char)c;
        fbuffer[i] = fq.getFreq(c);
        i++;
    }

    //  Writing into file
    outfile.write(buffer, sizeof(unsigned char) * numOfChars);
    outfile.write((char *)fbuffer, sizeof(unsigned) * numOfChars);

    //  Deletion of unneeded arrays
    delete[] buffer;
    delete[] fbuffer;

    //  Creating bitstream object
    bitstream bs(codeTable);

    input.clear();
    input.seekg(0, ios::beg);
    bool finished = false;

    //  Converting to bits and putting into file
    while (!finished)
    {
        char *buff = bs.convertNext(input, &finished);
        outfile.write(buff, 1);
    }
    delete[] codeTable;

    //  Printing information to terminal
    cout << argv[3] << " -> " << outfile.tellp() << " bytes" << endl;
    if (size < outfile.tellp())
    {
       cout << "*** Size of compressed file > size of source file ***" << endl;
    }

    //  Closing filereads
    outfile.close();
    input.close();
}

int main(int argc, char *argv[])
{
    if(argc != 4){
        cerr << "Wrong number of arguments" << endl;
    }
    if (argv[1][0] == '-' && argv[1][1] == 'c')
    {
        compress(argc, argv); // if choice is -c then compress
    }
    else if (argv[1][0] == '-' && argv[1][1] == 'd')
    {
        decompress(argc, argv); //if choice is -d then decompress
    }
    else
    {
        cerr << "Invalid command" << endl; //if not either of two commands then error
        return 0;
    }

    return (0);
}