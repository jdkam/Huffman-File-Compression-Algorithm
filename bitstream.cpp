#include "bitstream.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>

using namespace std;

bitstream::bitstream()
{
    buffer = 0;
    bufferLength = 0;
}

void bitstream::readIn()
{

    std::ifstream is("test.txt", std::ifstream::binary);
    if (is)
    {
        // get length of file:
        is.seekg(0, is.end);
        int length = is.tellg();
        is.seekg(0, is.beg);

        setBufferLength(length);
        

        char *buffer = new char[length]; //create a dynamic array of length of the file

        std::cout << "Reading " << length << " characters... ";
        // read data as a block:
        is.read(buffer, length);

        if (is)
        {
            std::cout << "all characters read successfully.";
            setBuffer(buffer);
        }
        else
        {
            std::cout << "error: only " << is.gcount() << " could be read";
        }
        is.close();


    //used for printing the buffer out
        //cout << "\nLength of buffer is: " << length << endl;
        //for (int i = 0; i < length; i++)
        //{
        //    cout << buffer[i];
        //}

        //return *buffer; //return a ptr to buffer

        // ...buffer contains the entire file...

        //delete[] buffer;
    }
}

bool bitstream::writeOut()
{
    std::ifstream infile("test.txt", std::ifstream::binary);
    std::ofstream outfile("new.txt", std::ofstream::binary);

    // get size of file
    infile.seekg(0, infile.end);
    long size = infile.tellg();
    infile.seekg(0);

    // allocate memory for file content
    char *buffer = new char[size];

    // read content of infile
    infile.read(buffer, size);

    // write to outfile
    outfile.write(buffer, size);

    // release dynamically-allocated memory
    delete[] buffer;

    outfile.close();
    infile.close();

    return true;
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
