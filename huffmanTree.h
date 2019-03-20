#pragma once
#include <string>
#include <fstream>

class huffmanTree
{

  private:
    unsigned weight, height;
    

    class Node
    {
      private:
        Node *left;
        Node *right;
        unsigned short val;

      public:
        Node(unsigned short val);
        unsigned short getVal();
        Node *getleft();
        Node *getright();
        void attachNodes(Node *a, Node *b);
    };

    Node *root;

   
 void code(Node* root, char *s,unsigned n,std::string str[]);
  public:

    huffmanTree(const huffmanTree &a, const huffmanTree &b);

    huffmanTree(unsigned weight, unsigned short c);

    huffmanTree();

    Node* returnRoot();

    char getC(std::ifstream &in, bool *done);

    void makeCodeTable(std::string *table);

    friend bool operator<(const huffmanTree &a, const huffmanTree &b);
    friend bool operator>(const huffmanTree &a, const huffmanTree &b);

    unsigned getWeight();



};