#include "huffmanTree.h"
#include <iostream>
#include <string>



huffmanTree::huffmanTree()
{
    this->weight = 0;
    this->root = NULL;
    this->height = 0;
}

huffmanTree::huffmanTree(unsigned weight, unsigned short c)
{
    root = new Node(c);
    this->weight = weight;
    this->height = 0;
}

huffmanTree::huffmanTree(const huffmanTree &a, const huffmanTree &b)
{
    this->weight = a.weight + b.weight;
    this->height = (a.height > b.height) ? a.height+1 : b.height + 1;
    this->root = new Node(512);
    this->root->attachNodes(a.root, b.root);
}

bool operator<(const huffmanTree &a, const huffmanTree &b)
{
    return a.weight < b.weight;
}

bool operator>(const huffmanTree &a, const huffmanTree &b)
{
    return a.weight > b.weight;
}

huffmanTree::Node::Node(unsigned short val) {
    this->val = val;
    this->left = nullptr;
    this->right = nullptr;
}

huffmanTree::Node* huffmanTree::returnRoot(){
    return root;
}


void huffmanTree::Node::attachNodes(huffmanTree::Node *left, huffmanTree::Node *right)
{
    this->left = left;
    this->right = right;
}

unsigned short huffmanTree::Node::getVal()
{
    return val;
}

huffmanTree::Node* huffmanTree::Node::getleft() {
    return left;
}

unsigned huffmanTree::getWeight(){
    return weight;
}


//returns the address of the right node
huffmanTree::Node* huffmanTree::Node::getright() {
    return right;
}

void huffmanTree::makeCodeTable(std::string *table){
  
    char s[height];
    code(root,s,0,table);
}

//Gets the next char from the tree to decode
char huffmanTree::getC(std::ifstream& in, bool* done){
     static char c;
    static short n = 8;
    huffmanTree::Node* node = root;
    for( ; ; ) {
        if(node->getVal() != 512){//check if node is not 0
            if(node->getVal() == 256) 
            *done = true;
            return (char)node->getVal();
        }
        if(n >= 8){
            if(!in.get(c)){
                *done = true;
                return 0;
            }
            n = 0;
        }
        int path = 0x80 & c;
        if (path)
            node = node->getright();
        else
            node = node->getleft();
        c <<= 1;
        n++;
    }

}
//Used to put the poppulate the tree
void huffmanTree::code(huffmanTree::Node* root, char* s,unsigned n,std::string table[]) {
    if(root->getVal() != 512){
        std::string code;
        s[n] = 0;
        code = s;
        table[root->getVal()] = s;
        return;
    }

    s[n]= '0';
    code(root->getleft(),s,n+1,table);

    s[n] = '1';
    code(root->getright(),s,n+1,table);

}
