#include <iostream>
#include "priorityQueue.h"
#include "frequencyCounter.h"


using namespace std;

class huffmanTree{

    char data;
    int freq;

    huffmanTree * left, *right;
    

    public:

    huffmanTree();
    //build tree
    //grab 2 char, create parent node with freq = sum of two node freq
    //peek, dequeue, peek, dequeue
    //calculate parent
    //enqueue parent into priority queue
    //stop when no more char to be queued

    void buildTree(freqCounter *newTable, int length);

    void setData(const char adata);
    char getData() const;

    void setFreq(const int afreq);
    int getFreq() const;

    //compute huffman code

    //obtain huffman code


bool operator < (const huffmanTree& f)
    {
        if(this->freq < f.getFreq())
        return true;
        else
        return false;
    }

    bool operator >(const huffmanTree &f){

        if(this->freq > f.getFreq())
        return true;
        else 
        return false;
    }
};
