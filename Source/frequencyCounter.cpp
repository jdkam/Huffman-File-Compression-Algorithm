/*  frequencyCounter.cpp
*   Desc: A Class that will count the frequency of 256 ascii characters in a file
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/


#include "frequencyCounter.h"
#include <iostream>

using namespace std;

//  Description:  Constructor
freqCounter::freqCounter()
{
}

 //  Description:  Desctructor
freqCounter::~freqCounter()
{
    delete[] freqarr;
}

//  Description:  Returns frequency at index c
unsigned freqCounter::getFreq(unsigned short c) 
{
    return freqarr[c];
}

//  Description:  Generates frequency table from input
freqCounter::freqCounter(std::ifstream& input) 
{

    freqarr = new unsigned[257]{0};

    if (!input.is_open()) 
    { 
        cout << "error: cant open file\n";
        return;
    }
    char character;
    while (input.get(character)) {
        freqarr[(unsigned char) character]++;
    }

    freqarr[256] = 1; // set end bit to 1
    //  ascii char to dec value is one to one with freqarr

}



