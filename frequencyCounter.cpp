#include "frequencyCounter.h"
#include <iostream>

using namespace std;

freqCounter::freqCounter()
{
    character = 0;
    freq = 0;
    uniqueLength = 0;
    codeWord = "";

}

//freqCounter::freqCounter(const freqCounter& f){
 //   
 //   character = f.getChar();
 //   freq = f.getFreq();
//}

char freqCounter::getChar() const{
    return character;
}

int freqCounter::getFreq() const{
    return freq;
}

int freqCounter::getUniqueLength() const{
    return uniqueLength;
}

void freqCounter::setFreq(const int aFreq){
    freq = aFreq;
}

void freqCounter::setChar(const char aChar){
    character = aChar;
}

void freqCounter::setCodeWord(const string astring){
    codeWord = astring;
}

string freqCounter::getCodeWord(){
    return codeWord;
}

freqCounter *freqCounter::getTable(){
    return mytable;
}

freqCounter* freqCounter::generateTable(int length, char *abuffer){
    
    freqCounter *mytable= new freqCounter[256];

    //initialize ascii values
    //initializing freq table to 0
    for (int i = 0; i < 256; i++)
    {
        mytable[i].setChar(i);
        mytable[i].setFreq(0);
        
    }

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

        if(mytable[asciiValue].getFreq() == 1)
        {
            uniqueLength++;
        }

    }

    //print freqTable
    /*
    cout << "\nPRINTING FREQUENCY TABLE\n";
    for(int i=0; i<255; i++)
    {
        if(mytable[i].getFreq() != 0){
        cout << mytable[i].getChar() << " : ";
        cout << mytable[i].getFreq() << endl;
       }
    }
    */

    return mytable;
}

