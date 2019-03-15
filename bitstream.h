#pragma once

#include <iostream>
#include <string>

#include "frequencyCounter.h"

class bitstream
{
    char * buffer;
    int bufferLength;

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

    int getBufferLength() const;
    void setBufferLength(const int aLength);

    char *getBuffer();
    void setBuffer(char *aBuffer);

    void readIn(); //reads input and updates freq of characters

    bool writeOut();

};