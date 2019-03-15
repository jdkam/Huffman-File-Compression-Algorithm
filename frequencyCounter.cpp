#include "frequencyCounter.h"
#include <iostream>

using namespace std;

freqCounter::freqCounter()
{
    character = 0;
    freq = 0;
}

char freqCounter::getChar() const
{
    return *character;
}

int freqCounter::getFreq() const
{
    return *freq;
}

void freqCounter::setFreq(int *aFreq)
{
    freq = aFreq;
}

void freqCounter::setChar(char *aChar)
{
    character = aChar;
}

void freqCounter::generateTable(int length, char *abuffer)
{

    //need array for ascii
    //need array for freq values

    char *ascii = new char[256];
    int *freqValue = new int[256];

    //initialize ascii values

    for (int i = 0; i < 256; i++)
    {
        ascii[i] = i;
    }

    char thisChar;
    int asciiValue =0;

    //parse buffer char by char
    for(int k =0; k<length; k++)
    {
        thisChar = abuffer[k];
        cout << toascii(thisChar) << endl;
        asciiValue = toascii(thisChar);
        freqValue[asciiValue]++;
    }

    //print freqTable
    for(int i=0; i<256; i++)
    {
        cout << ascii[i] << " : ";
        cout << freqValue[i] << endl;
    }
}