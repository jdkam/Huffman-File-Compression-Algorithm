#include "bitstream.h"
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include "frequencyCounter.h"

using namespace std;

bitstream::bitstream()
{
    buffer = 0;
    bufferLength = 0;
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

void bitstream::writeOut(string code, string* tableBuffer, int tableLength)
{
    //std::ifstream infile("test.txt", std::ifstream::binary);
    std::ofstream outfile("compressed.txt");

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

    if(outfile.is_open())
    {
        outfile << code;
        
        outfile << endl;
        for(int i=0; i<tableLength; i++){
            outfile << tableBuffer[i];
            outfile << endl;
        }
    }

    outfile.close();
   // infile.close();

    return;
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
