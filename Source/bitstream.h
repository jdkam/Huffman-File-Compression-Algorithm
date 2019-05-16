/*  bitstream.h
*   Desc: A Class that will encode and decode single bits from file stream
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/
#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "frequencyCounter.h"

using namespace std;

class bitstream
{
  private:
    //  Description:  Stores the characters in a char array
    char *buffer;

    //  Description:  Amount of characters from file
    int bufferLength;

    //  Description:  Stores huffman code
    string *codeTable;

    //  Description:  Carry bit
    string carry;

  public:
    //  Description:  Constructor
    bitstream();

    //  Description:  Destructor
    ~bitstream(); 

    //  Description:  Paramaterized constructor
    bitstream(string *codeTable);

    //  Description:  Returns the amount of characters from file
    int getBufferLength() const;
    //  Description:  Getter for buffer
    char *getBuffer();

    //  Description:  Setter for buffer
    void setBuffer(char *aBuffer);
    //  Description:  Setter for bufferLength
    void setBufferLength(const int aLength);


    //  Description:  Converts file characters to bits
    char *convertNext(std::ifstream &in, bool *finished);
};
