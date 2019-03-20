#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "frequencyCounter.h"

using namespace std;

class bitstream
{
    char * buffer;
    int bufferLength;

    string *codeTable;
    string carryOver;

public:

    //what should this class do?
    //read input, store it into a file stream (buffer)
    //buffer to be used by the frequencyCounter
    //there is 256 possible char
    
    //output hoffman code to a file stream (output file)
    //each character is 8 bits long (1 byte = 8 bits)
    //which is why we need to write a sequence of 8 bits
    //2^8 = 256 = 256 possible ascii characters
    //each bit sequence is unique (class invariant)

    bitstream();
    ~bitstream(); //destructor

     bitstream(string* codeTable);
    int getBufferLength() const;
    void setBufferLength(const int aLength);

    char *getBuffer();
    void setBuffer(char *aBuffer);

    void readIn(char *a); //reads input and updates freq of characters

    void writeOut(string code, string* tableBuffer, int tableLength, char* s);

    char* getNext(std::ifstream& in, bool* done);
};

