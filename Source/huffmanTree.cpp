/*
*   huffmanTree.cpp
*   Desc: A Class that will generate huffman tree
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/


#include "huffmanTree.h"
#include <iostream>
#include <string>

using namespace std;


//  Description: Constructor
huffmanTree::huffmanTree()
{
    this->weight = 0;
    this->root = NULL;
    this->height = 0;
}

 //  Description: Paramaterized constructors
huffmanTree::huffmanTree(unsigned weight, unsigned short c)
{
    root = new Node(c);
    this->weight = weight;
    this->height = 0;
}

 //  Description: Paramaterized constructors
huffmanTree::huffmanTree(const huffmanTree &a, const huffmanTree &b)
{
    this->weight = a.weight + b.weight;
    this->height = (a.height > b.height) ? a.height+1 : b.height + 1;
    this->root = new Node(512);
    this->root->attachNodes(a.root, b.root);
}

//  Description: Paramaterized constructor
huffmanTree::Node::Node(unsigned short val) {
    this->val = val;
    this->left = NULL;
    this->right = NULL;
}

//  Description:  Joinage of nodes
void huffmanTree::Node::attachNodes(huffmanTree::Node *left, huffmanTree::Node *right)
{
    this->left = left;
    this->right = right;
}

//  Description: Get val
unsigned short huffmanTree::Node::getVal()
{
    return val;
}
//  Description: Get left and right nodes
huffmanTree::Node* huffmanTree::Node::getleft() 
{
    return left;
}
huffmanTree::Node* huffmanTree::Node::getright() 
{
    return right;
}

 //  Description: Getter for node and weight
unsigned huffmanTree::getWeight(){
    return weight;
}
huffmanTree::Node* huffmanTree::returnRoot()
{
    return root;
}

//  Description: Creates huffman coding
void huffmanTree::makeCodeTable(std::string *table)
{
    char str[height];
    code(root,str,0,table);
}

//  Description: Traverses tree to get ascii
char huffmanTree::getC(std::ifstream& in, bool* finished)
{
    static char x;
    static short y = 8;
    huffmanTree::Node* node = root;
    for( ; ; ) 
    {
        if(node->getVal() != 512)
        {
            if(node->getVal() == 256) 
            *finished = true;
            return (char)node->getVal();
        }
        if(y >= 8){
            if(!in.get(x))
            {
                *finished = true;
                return 0;
            }
            y = 0;
        }
        int z = 0x80 & x;
        if (z)
        {
            node = node->getright();
        }
        else
        {
            node = node->getleft();
        }
        x <<= 1;
        y++;
    }
}

//  Description: Populates array by traversing huffman tree
void huffmanTree::code(huffmanTree::Node* root, char* str, unsigned n, string table[]) 
{
    if(root->getVal() != 512)
    {
        string code;
        str[n] = 0;
        code = str;
        table[root->getVal()] = str;
        return;
    }

    str[n]= '0';
    code(root->getleft(),str,n+1,table);

    str[n] = '1';
    code(root->getright(),str,n+1,table);

}

//  Description: Overload operators
bool operator<(const huffmanTree &a, const huffmanTree &b)
{
    return a.weight < b.weight;
}
bool operator>(const huffmanTree &a, const huffmanTree &b)
{
    return a.weight > b.weight;
}