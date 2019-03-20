/*
frequencyCounter.h
Desc: A Class that will count the frequency of 256 ascii characters in a file and generate
a "frequency table" using an array
*/

#pragma once
#include <iostream>
#include <string>
#include "bitstream.h"

using namespace std;

class freqCounter{   
    //private members
    unsigned char character;
    unsigned int freq;
    int uniqueLength;
    string codeWord;
    freqCounter *mytable;

    public:

    freqCounter();

    //freqCounter(const freqCounter & f);

    //getters
    char getChar() const;
    unsigned int getFreq() const;
    int getUniqueLength() const;


    //setters
    void setChar(const char aChar); //do we need this? if reading char from file?
    void setFreq( const int aFreq);

    void setCodeWord(const string astring);
    std::string getCodeWord();
    
    //generates the frequency table by reading
    //in the buffer and updating freq of each ascii char
    freqCounter* generateTable(int length, char *abuffer);

    freqCounter* getTable();

    bool operator < (const freqCounter& f)
    {
        if(this->freq < f.getFreq())
        return true;
        else
        return false;
    }

    bool operator >(const freqCounter &f){

        if(this->freq > f.getFreq())
        return true;
        else 
        return false;
    }
    

	
};