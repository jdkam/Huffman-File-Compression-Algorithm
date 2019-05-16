/*  bitstream.cpp
*   Desc: A Class that will encode and decode single bits from file stream
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/

#include "bitstream.h"
#include <iostream>

#include <fstream>
#include <istream>
#include "frequencyCounter.h"

using namespace std;

//  Description:  Constructor
bitstream::bitstream()
{
    buffer = 0;
    bufferLength = 0;
}

//  Description:  Destructor
bitstream::~bitstream()
{
    delete[] buffer;
}

//  Description:  Paramaterized constructor
bitstream::bitstream(string *codeTable)
{
    this->buffer = new char[1];
    this->codeTable = codeTable;
}

//  Description:  Converts file characters to bits
char *bitstream::convertNext(std::ifstream &in, bool *finished)
{
    static bool endOfFile;
    unsigned char buffering = 0; 
    char c;
    std::string code = carry;
    int index = 0;
    
    while(true)
    {
        for (int j = 0; j < code.length(); j++)
        {
            buffering <<= 1; 
            index++;

            if (code.at(j) == '1')
            {
                buffering |= 0x1; 
            }
            if (index >= 8)
            { 
                carry = code.substr(j + 1);
                break; 
            }
        }
        if (index >= 8)
        {
            break; 
        }
        if (endOfFile)
        { 
            *finished = true;
            buffering <<= (8 - index); 
            break;
        }
        if (!in.get(c))
        {
            code = codeTable[256];
            endOfFile = true;
        }
        else
        {
            code = codeTable[(unsigned char)c];
        }
    }

    *buffer = buffering;
    return buffer;
}



//  Description:  Getters
int bitstream::getBufferLength() const
{
    return bufferLength;
}
//  Description:  Getter for buffer
char *bitstream::getBuffer()
{
    return buffer;
}


//  Description:  Returns the amount of characters from file
void bitstream::setBufferLength(const int aLength)
{
    bufferLength = aLength;
}
//  Description:  Setter for buffer
void bitstream::setBuffer(char *aBuffer)
{
    buffer = aBuffer;
}




