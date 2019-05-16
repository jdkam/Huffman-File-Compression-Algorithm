/*  huffmanTree.h
*   Desc: A Class that will generate huffman tree
*   Author: Jordan Kam and Kent Huang
*   Date: March 20, 2019
*/

#pragma once
#include <string>
#include <fstream>

class huffmanTree
{

  private:

    //  Description: weight and height of tree
    unsigned weight, height;
    
    //  Description: Node class for tree joining
    class Node
    {
      private:
        Node *left;
        Node *right;
        unsigned short val;

      public:
        //  Description: Paramaterized constructor
        Node(unsigned short val);

        //  Description: Getter
        unsigned short getVal();

        //  Description: Get left and right nodes
        Node *getleft();
        Node *getright();

        //  Description:  Joinage of nodes
        void attachNodes(Node *a, Node *b);
    };

    //  Description: Root of tree
    Node *root;
   
    //  Description: Populates array by traversing huffman tree
    void code(Node* root, char *s,unsigned n,std::string str[]);

  public:
    //  Description: Constructor
    huffmanTree();

    //  Description: Paramaterized constructors
    huffmanTree(const huffmanTree &a, const huffmanTree &b);
    huffmanTree(unsigned weight, unsigned short c);

    //  Description: Getter for node and weight
    Node* returnRoot();
    unsigned getWeight();

    //  Description: Traverses tree to get ascii
    char getC(std::ifstream &in, bool *finished);

    //  Description: Creates huffman coding
    void makeCodeTable(std::string *table);

    //  Description: Overload operators
    friend bool operator<(const huffmanTree &a, const huffmanTree &b);
    friend bool operator>(const huffmanTree &a, const huffmanTree &b);

    
    



};