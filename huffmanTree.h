#include <iostream>
#include "priorityQueue.h"
#include "frequencyCounter.h"
#define COUNT 10


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

    void print2DUtil(huffmanTree *root, int space);

    void print2D(huffmanTree *root);

    huffmanTree* formNodes(huffmanTree first, huffmanTree second);


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

   