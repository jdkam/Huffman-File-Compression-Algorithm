/*  frequencyCounter.h
*   Desc: A Class that will count the frequency of 256 ascii characters in a file
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/

#pragma once
#include <iostream>
#include <string>
#include "bitstream.h"

using namespace std;

class freqCounter
{

    private:

        //  Description:  Positive integer array
        unsigned *freqarr;

    public:
        //  Description:  Constructor
        freqCounter();

        //  Description:  Desctructor
        ~freqCounter();

        //  Description:  Returns frequency at index c
        unsigned getFreq(unsigned short c); //positive 1 byte num

        //  Description:  Generates frequency table from input
        freqCounter(ifstream &input);



 

    
};