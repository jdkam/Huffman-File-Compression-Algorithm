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

huffmanTree* makeTree(PriorityQueue<huffmanTree> huffTree, int length){

    //called recursively
    




}


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

    //  huffmanTree t;
    //  for (int i = 0; i < length; i++)
    //  {

    //          t = huffTree.peek();
    //         cout << t.getData() << endl;
    //          huffTree.dequeue();

    // }

    // huffmanTree first, second;
    // int sum = 0;
    // //huffmanTree *internalNode = new huffmanTree();
    // huffmanTree *pointerNode;

    // for (int i = 0; i < length + 1; i++)
    // {
    //         huffmanTree *internalNode = new huffmanTree();
    //         first = huffTree.peek();
    //         huffTree.dequeue();
    //         length--;

    //         //cout << first.getData() << endl;
    //         second = huffTree.peek();
    //         huffTree.dequeue();
    //         length--;
    //         //cout << second.getData() << endl;
    //         if (first.getFreq() == second.getFreq() || first.getFreq() < second.getFreq())
    //         {
    //             sum = first.getFreq() + second.getFreq();

    //             internalNode->setFreq(sum);
    //             internalNode->setData('x'); //

    //             huffmanTree *leftNode = new huffmanTree();
    //             huffmanTree *rightNode = new huffmanTree();

    //             leftNode->left = NULL;
    //             leftNode->right = NULL;

    //             rightNode->left = NULL;
    //             rightNode->right = NULL;

    //             leftNode->setData(first.getData());
    //             leftNode->setFreq(first.getFreq());
    //             //cout << first.getData() << endl;
    //             //cout << first.getFreq() << endl;

    //             rightNode->setData(second.getData());
    //             rightNode->setFreq(second.getFreq());
    //             //cout << second.getData() << endl;

    //             internalNode->left = leftNode;
    //             internalNode->right = rightNode;

    //             cout << "internal Node left child:" << internalNode->left->getData() << endl;
    //             cout << "internal Node right child: " << internalNode->right->getData() << endl;

    //             huffTree.enqueue(*internalNode);
    //             length++;
    //         }
    //         else if (first.getFreq() > second.getFreq())
    //         {
    //             sum = first.getFreq() + second.getFreq();

    //             internalNode->setFreq(sum);
    //             internalNode->setData('x'); //

    //             huffmanTree *leftNode = new huffmanTree();
    //             huffmanTree *rightNode = new huffmanTree();

    //             leftNode->left = NULL;
    //             leftNode->right = NULL;

    //             rightNode->left = NULL;
    //             rightNode->right = NULL;

    //             rightNode->setData(first.getData());
    //             rightNode->setFreq(first.getFreq());

    //             leftNode->setData(second.getData());
    //             leftNode->setFreq(second.getFreq());

    //             internalNode->left = leftNode;
    //             internalNode->right = rightNode;

    //             huffTree.enqueue(*internalNode);
    //             length++;
    //         }
    //         pointerNode = internalNode;
        
    // }
    // cout << pointerNode->left->right->getData() << " : " << pointerNode->left->right->getFreq() << endl;

    // huffmanTree test;

    // test.print2D(pointerNode);

    // /*
    // for (int i = 0; i < length; i++)
    // {
    //     test = huffTree.peek();

    //     cout << test.getData() << " : " << test.getFreq() << endl;

    //     huffTree.dequeue();
    //     length--;
    // }

}

void huffmanTree::print2DUtil(huffmanTree *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void huffmanTree::print2D(huffmanTree *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
