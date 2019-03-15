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

class freqCounter
{
    //private members
    char *character; 
    int *freq;

    public:

    freqCounter();

    //getters
    char getChar() const;
    int getFreq() const;


    //setters
    void setChar( char *aChar); //do we need this? if reading char from file?
    void setFreq( int *aFreq);

    //generates the frequency table by reading
    //in the buffer and updating freq of each ascii char
    void generateTable(int length, char *abuffer);

};