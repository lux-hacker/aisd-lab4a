#ifndef LAB4A_VIEW_H
#define LAB4A_VIEW_H

#include "../model/BinTree.h"
#include "stdio.h"

typedef struct Trunk{
    struct Trunk* prev;
    char* str;
} Trunk;

void printMenu();
void printTree(BinTreeNode*, Trunk*, int);
void printVector(Vector*);

#endif //LAB4A_VIEW_H
