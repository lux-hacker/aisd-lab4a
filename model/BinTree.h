#ifndef LAB4A_BINTREE_H
#define LAB4A_BINTREE_H

#include "stdio.h"

typedef struct BinTreeNode{
    unsigned int key;
    unsigned int data;
    struct BinTreeNode* left;
    struct BinTreeNode* right;
    struct BinTreeNode* parent;

} BinTreeNode;

typedef struct BinTree{
    BinTreeNode* root;
} BinTree;

typedef struct Vector{
    unsigned int* data;
    unsigned int size;
} Vector;

Vector* dfs(BinTree*, unsigned int, unsigned int, Vector*);
void addNewElement(BinTree*, unsigned int, unsigned int);
int deleteElement(BinTree*, unsigned int);
BinTreeNode* findByKey(BinTree*, unsigned int, unsigned int);
BinTreeNode* findMin(BinTree*, unsigned int);

void freeTree(BinTree*);



#endif
