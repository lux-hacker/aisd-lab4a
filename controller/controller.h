#ifndef LAB4A_CONTROLLER_H
#define LAB4A_CONTROLLER_H

#include "../view/view.h"
#include "../model/BinTree.h"

unsigned int getUInt();
void menu();

char* freadline(FILE*);
int importFromFile(BinTree*);

void timing(BinTree*);


#endif //LAB4A_CONTROLLER_H
