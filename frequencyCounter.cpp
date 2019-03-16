#include "frequencyCounter.h"
#include <iostream>

using namespace std;

freqCounter::freqCounter()
{
    character = 0;
    freq = 0;
    //freqCounter *mytable = new freqCounter[255];

}

//freqCounter::freqCounter(const freqCounter& f){
 //   
 //   character = f.getChar();
 //   freq = f.getFreq();
//}

char freqCounter::getChar() const
{
    return character;
}

int freqCounter::getFreq() const
{
    return freq;
}

void freqCounter::setFreq(const int aFreq)
{
    freq = aFreq;
}

void freqCounter::setChar(const char aChar)
{
    character = aChar;
}

freqCounter *freqCounter::getTable(){
    return mytable;
}

freqCounter* freqCounter::generateTable(int length, char *abuffer)
{

    //need array for ascii
    //need array for freq values

    //char *ascii = new char[255];
    //int *freqValue = new int[255];
    freqCounter *mytable= new freqCounter[255];

    //mytable[0].setChar('a');
    //mytable[0].setFreq(1);

    //cout << mytable[0].getChar() << " : " << mytable[0].getFreq() << endl; 
    //initialize ascii values
    //initializing freq table to 0
    for (int i = 0; i < 255; i++)
    {
        mytable[i].setChar(i);
        mytable[i].setFreq(0);
        
    }

   
    //for(int k=0; k < 255; k++){
     //   cout << mytable->character[k] << " : " << mytable->freq[k] << endl;
    //}

    //need an array of objects?

    char thisChar;
    int asciiValue = 0;

    //parse buffer char by char
    for(int k =0; k<length; k++)
    {
        thisChar = abuffer[k];
        //cout << toascii(thisChar) << endl;
        asciiValue = toascii(thisChar);

        mytable[asciiValue].setFreq(mytable[asciiValue].getFreq()+1);
        mytable[asciiValue].setChar(thisChar);

    }

    //print freqTable
    cout << "\nPRINTING FREQUENCY TABLE\n";
    for(int i=0; i<255; i++)
    {
        if(mytable[i].getFreq() != 0){
        cout << mytable[i].getChar() << " : ";
        cout << mytable[i].getFreq() << endl;
       }
    }

    return mytable;
}