#include <iostream>
#include "huffmanTree.h"

huffmanTree::huffmanTree()
{
    freq = 0;
    data = 0;
    left, right = NULL;
}

void huffmanTree::setData(const char adata)
{
    data = adata;
}

char huffmanTree::getData() const
{
    return data;
}

void huffmanTree::setFreq(const int afreq)
{
    freq = afreq;
}

int huffmanTree::getFreq() const
{
    return freq;
}

void convertToHuff(freqCounter *newTable, int length);

void huffmanTree::buildTree(freqCounter *newTable, int length)
{

    //conver to huffman queue
    PriorityQueue<huffmanTree> huffTree;
    huffmanTree *myNode = new huffmanTree();
    for (int i = 0; i < 255; i++)
    {
        if (newTable[i].getFreq() != 0)
        {
            //cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
            myNode->setData(newTable[i].getChar());
            myNode->setFreq(newTable[i].getFreq());

            huffTree.enqueue(*myNode);
        }
    }

    huffmanTree t;
    for (int i = 0; i < length; i++)
    {
        
            t = huffTree.peek();
            cout << t.getData() << endl;
            huffTree.dequeue();
        
    }

    huffmanTree first, second;
    int sum = 0;
    huffmanTree *internalNode = new huffmanTree();

    for (int i = 0; i < length + 1; i++)
    {
        first = huffTree.peek();
        huffTree.dequeue();
        length--;

        //cout << first.getData() << endl;
        second = huffTree.peek();
        huffTree.dequeue();
        length--;
        //cout << second.getData() << endl;
        if (first.getFreq() == second.getFreq() || first.getFreq() < second.getFreq())
        {
            sum = first.getFreq() + second.getFreq();

            internalNode->setFreq(sum);
            internalNode->setData('x'); //

            huffmanTree *leftNode = new huffmanTree();
            huffmanTree *rightNode = new huffmanTree();

            leftNode->setData(first.getData());
            leftNode->setFreq(first.getFreq());

            rightNode->setData(second.getData());
            rightNode->setFreq(second.getFreq());

            internalNode->left = leftNode;
            internalNode->right = rightNode;

            //cout << internalNode->left->getData();

            huffTree.enqueue(*internalNode);
            length++;
        }
        else if(first.getFreq() > second.getFreq())
        {
            sum = first.getFreq() + second.getFreq();

            internalNode->setFreq(sum);
            internalNode->setData('x'); //

            huffmanTree *leftNode = new huffmanTree();
            huffmanTree *rightNode = new huffmanTree();

            rightNode->setData(first.getData());
            rightNode->setFreq(first.getFreq());

            leftNode->setData(second.getData());
            leftNode->setFreq(second.getFreq());

            internalNode->left = leftNode;
            internalNode->right = rightNode;

            huffTree.enqueue(*internalNode);
            length++;

            
        }

    }
       //cout << internalNode->left->right->getData() << endl;


    huffmanTree test;
    

    /*
    for (int i = 0; i < length; i++)
    {
        test = huffTree.peek();

        cout << test.getData() << " : " << test.getFreq() << endl;

        huffTree.dequeue();
        length--;
    }
*/

}