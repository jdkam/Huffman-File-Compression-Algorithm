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

void huffmanTree::buildTree(freqCounter *newTable, int length)
{

    //conver to huffman queue
    PriorityQueue<huffmanTree> huffTree;
    huffmanTree *myNode = new huffmanTree();
    for (int i = 0; i < 256; i++)
    {
        if (newTable[i].getFreq() != 0)
        {
            //cout << newTable[i].getChar() << " : " << newTable[i].getFreq() << endl;
            myNode->setData(newTable[i].getChar());
            myNode->setFreq(newTable[i].getFreq());
            cout <<  myNode->getData() << " : " <<  myNode->getFreq() << endl;

            huffTree.enqueue(*myNode);
        }
    }

    //  huffmanTree t;
    //  for (int i = 0; i < length; i++)
    //  {

    //          t = huffTree.peek();
    //         cout << t.getData() << " : " << t.getFreq() << endl;
            
    //          huffTree.dequeue();

    // }

   

    // huffmanTree *internalNode = new huffmanTree();

    // first = huffTree.peek();
    // huffTree.dequeue();
    // length--;

    // second = huffTree.peek();
    // huffTree.dequeue();
    // length--;

    // huffmanTree *leftNode = &first;
    // huffmanTree *rightNode = &second;

    // //leftNode->setData(first.getData());
    // //leftNode->setFreq(first.getFreq());

    // //rightNode->setData(second.getData());
    // //rightNode->setFreq(second.getFreq());
    // sum = first.getFreq() + second.getFreq();

    // cout << leftNode->getData() << " : " << leftNode->getFreq() << "this should be a: 1" << endl;
    // cout << rightNode->getData() << " : " << rightNode->getFreq() << "this should be l:1" << endl;

    // //leftNode->left = NULL;
    // //leftNode->right = NULL;

    // //rightNode->left = NULL;
    // //rightNode->right = NULL;

    // internalNode->left = leftNode;
    // internalNode->right = rightNode;

    // internalNode->setData('x');
    // internalNode->setFreq(sum);

    // huffTree.enqueue(*internalNode);

    // cout << internalNode->getData() << " : " << internalNode->getFreq() << "This Parent Node should be x, with value 2" << endl;

    // cout << internalNode->left->getData() << " : " << internalNode->left->getFreq() << endl;
    // cout << internalNode->right->getData() << " : " << internalNode->right->getFreq() << endl;

    // //second iteration
    // huffmanTree *internalNode2 = new huffmanTree();

    // first = huffTree.peek();
    // huffTree.dequeue();
    // length--;
    // cout << first.getData() << endl;
    // cout << "\ntest1\n";
    // second = huffTree.peek();
    // huffTree.dequeue();
    // length--;
    // cout << second.getData() << endl;

    // huffmanTree *leftNode2 = &first;
    // huffmanTree *rightNode2 = &second;

    // cout << "\ntest2\n";
    // //leftNode2->setData(first.getData());
    // //leftNode2->setFreq(first.getFreq());

    // //rightNode2->setData(second.getData());
    // //rightNode2->setFreq(second.getFreq());
    // //cout << rightNode2->right->getData();
    // sum = first.getFreq() + second.getFreq();
    // cout << leftNode2->getData() << " : " << leftNode2->getFreq() << "this should be l : 1" << endl;
    // //cout << rightNode2->getData() << " : " << rightNode2->getFreq() << "this should be x : 2" << endl;
    // cout << "\ntest3\n";
    // //leftNode2->left = NULL;
    // // leftNode2->right = NULL;

    // //rightNode2->left = NULL;
    // //rightNode2->right = NULL;
    // cout << "\ntest4\n";
    // internalNode2->left = leftNode2;
    // cout << "\ntest5\n";
    // internalNode2->right = rightNode2;
    // cout << rightNode2->right->getData() << endl;
    // cout << "internalnode2 right: " << internalNode2->right->right->getData() << " : " << internalNode2->right->right->getFreq();
    // cout << "\ntest6\n";

    // internalNode2->setData('x');
    // cout << "\ntest7\n";
    // internalNode2->setFreq(sum);

    // cout << internalNode2->getData() << " : " << internalNode2->getFreq() << "This Parent Node should be x, with value 3" << endl;

    // cout << internalNode2->left->getData() << " : " << internalNode2->left->getFreq() << endl;
    // cout << internalNode2->right->getData() << " : " << internalNode2->right->getFreq() << endl;
    // cout << "\ntest8\n";

    // cout << "Printing root right right\n"
    //      << internalNode2->right->getData() << " : " << internalNode2->right->getFreq() << endl;
    // //cout << internalNode2->left->getData() << " : " << internalNode2->left->getFreq() << endl;
     huffmanTree first, second;
    int sum = 0;
    huffmanTree *pointerNode;

    while (huffTree.getElementCount() > 1)
    {
        huffmanTree *internalNode = new huffmanTree();
        huffmanTree *leftNode = &first;
        huffmanTree *rightNode = &second;
        first = huffTree.peek();
        huffTree.dequeue();
        length--;
        cout << "First peek: " << first.getData() << " : " << first.getFreq() << endl;

        if (0 == length)
            break;

        second = huffTree.peek();
        huffTree.dequeue();
        length--;
        cout << "Second peek: " << second.getData() << " : " << second.getFreq() << endl;

        int sum = first.getFreq() + second.getFreq();

        internalNode->setFreq(sum);
        internalNode->setData('x'); //

        if (leftNode->getFreq() < rightNode->getFreq())
        {
            internalNode->left = leftNode;
            internalNode->right = rightNode;
        }
        else
        {
            internalNode->left = rightNode;
            internalNode->right = leftNode;
        }

        huffTree.enqueue(*internalNode);
        length++;
        pointerNode = internalNode;
        cout << "# of elements in PQ: " << huffTree.getElementCount() << endl;
    }

    cout << pointerNode->left->left->getData() << " : " << pointerNode->left->left->getFreq() << endl;
   // huffmanTree test;
    //test.print2D(pointerNode);
    // cout << second.getData() << endl;
    // if (first.getFreq() == second.getFreq() || first.getFreq() < second.getFreq())
    // {
    //     sum = first.getFreq() + second.getFreq();

    //     internalNode->setFreq(sum);
    //     internalNode->setData('x'); //

    //     huffmanTree *leftNode = new huffmanTree();
    //     huffmanTree *rightNode = new huffmanTree();

    //     leftNode->left = NULL;
    //     leftNode->right = NULL;

    //     rightNode->left = NULL;
    //     rightNode->right = NULL;

    //     leftNode->setData(first.getData());
    //     leftNode->setFreq(first.getFreq());
    //     //cout << first.getData() << endl;
    //     //cout << first.getFreq() << endl;

    //     rightNode->setData(second.getData());
    //     rightNode->setFreq(second.getFreq());
    //     //cout << second.getData() << endl;

    //     internalNode->left = leftNode;
    //     internalNode->right = rightNode;

    //     //cout << "internal Node left child:" << internalNode->left->getData() << endl;
    //     //cout << "internal Node right child: " << internalNode->right->getData() << endl;

    //     huffTree.enqueue(*internalNode);
    //     length++;
    // }
    // else if (first.getFreq() > second.getFreq())
    // {
    //     sum = first.getFreq() + second.getFreq();

    //     internalNode->setFreq(sum);
    //     internalNode->setData('x'); //

    //     huffmanTree *leftNode = new huffmanTree();
    //     huffmanTree *rightNode = new huffmanTree();

    //     leftNode->left = NULL;
    //     leftNode->right = NULL;

    //     rightNode->left = NULL;
    //     rightNode->right = NULL;

    //     rightNode->setData(first.getData());
    //     rightNode->setFreq(first.getFreq());

    //     leftNode->setData(second.getData());
    //     leftNode->setFreq(second.getFreq());

    //     internalNode->left = leftNode;
    //     internalNode->right = rightNode;

    //     huffTree.enqueue(*internalNode);
    //     length++;
    // }
    // pointerNode = internalNode;
    // i++;

    // }

    // huffmanTree test;
    //test.print2D(internalNode2);

    // for (int i = 0; i < length; i++)
    // {
    //     test = huffTree.peek();

    //     cout << test.getData() << " : " << test.getFreq() << endl;

    //     huffTree.dequeue();
    //     length--;
    // }
}

huffmanTree *huffmanTree::formNodes(huffmanTree first, huffmanTree second)
{

    // int sum = first.getFreq() + second.getFreq();
    // huffmanTree *internalNode = new huffmanTree();

    // internalNode->setFreq(sum);
    // internalNode->setData('x'); //

    // huffmanTree *leftNode = first;
    // huffmanTree *rightNode = second;

    // // leftNode->left = NULL;
    // // leftNode->right = NULL;

    // // rightNode->left = NULL;
    // // rightNode->right = NULL;

    // internalNode->left = leftNode;
    // internalNode->right = rightNode;

    // // else
    // // {
    // //     internalNode->left = leftNode;
    // //     internalNode->right = rightNode;
    // // }
    // return internalNode;
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
