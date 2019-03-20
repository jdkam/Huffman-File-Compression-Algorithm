#include "bitstream.h"
#include <iostream>

#include <fstream>
#include <istream>
#include "frequencyCounter.h"

using namespace std;

bitstream::bitstream()
{
    buffer = 0;
    bufferLength = 0;

}


bitstream::bitstream(string* codeTable) {
    this->buffer = new char[1];
    this->codeTable = codeTable;
}

void bitstream::readIn(char* a)
{

    std::ifstream is(a, std::ifstream::binary);
    
    if (is)
    {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        setBufferLength(length);
        

        char *buffer = new char[length]; //create a dynamic array of length of the file

        

        //std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read(buffer, length);


        if (is)
        {
            //std::cout << "all characters read successfully.";
            setBuffer(buffer);
        }
        else
        {
            std::cout << "error: only " << is.gcount() << " could be read";
        }
        //is.close();
 is.clear();
    is.seekg(0,ios::beg);

    //used for printing the buffer out
        //cout << "\nLength of buffer is: " << length << endl;
        //for (int i = 0; lengthi++)
        //{
        //    cout << bufflength
        //}

        //return *buffer; lengthtr to buffer

        // ...buffer contalengthre file...

        //delete[] buffer;length
    }
}

void bitstream::writeOut(string code, string* tableBuffer, int tableLength, char* s)
{
    //std::ifstream infile("test.txt", std::ifstream::binary);
    std::ofstream outfile(s);

    // get size of file
    //infile.seekg(0, infile.end);
    //long size = infile.tellg();
    //infile.seekg(0);

    // allocate memory for file content
   // char *buffer = new char[size];

    // read content of infile
    //infile.read(buffer, size);

    // write to outfile
    //outfile.write(code, code.size());

    // release dynamically-allocated memory
    //delete[] buffer;

    int bits;
    int size=0;
    if(outfile.is_open())
    {
        outfile << code;
        bits = code.size();

        outfile << endl;
        for(int i=0; i<tableLength; i++){
            outfile << tableBuffer[i];
            size += tableBuffer[i].size();
            
            if(i==tableLength-1)
            break;
            outfile << endl;
        }
       
    }

    outfile.close();
    //infile.close();

    return;
}

char* bitstream::getNext(std::ifstream& in, bool* done) {
    static bool onEof;
    unsigned char buff = 0; // buff al 0s.
    char c;
    std::string code = carryOver;
    int i = 0;
    for( ; ; ) {
        for (unsigned j = 0; j < code.length(); j++) {
            i++;
            buff <<= 1; // right shift buff.
            if (code.at(j) == '1')buff |= 0x1;  // checks if the string code has '1' at jth position and makes buff = 1 if it does
            if (i >= 8) {   //when i is at least 8, change carryover to the changed code from above
                carryOver = code.substr(j + 1);
                break; //move out of the nested loop
            }
        }
        if (i >= 8)break; // move out of the final loop.

        if(onEof){  //if file ends
            *done = true;
            buff <<= (8-i); // if the last 8 bits not complete, we shift it.
            break;
        }

        if (!in.get(c)) {
            code = codeTable[256];
            onEof = true;
        } else {
            code = codeTable[(unsigned char)c];
        }
    }

    *buffer = buff;
    return buffer;
}


int bitstream::getBufferLength() const{
    return bufferLength;
}

void bitstream::setBufferLength(const int aLength){
    bufferLength = aLength;
}

char *bitstream::getBuffer(){
    return buffer;
}

void bitstream::setBuffer( char *aBuffer){
    buffer = aBuffer;
}

bitstream::~bitstream(){
    delete[] buffer;
}

