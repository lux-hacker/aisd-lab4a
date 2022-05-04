#ifndef LAB4A_CONTROLLER_H
#define LAB4A_CONTROLLER_H

#include "../view/view.h"
#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"

unsigned int getUInt();
void menu();

char* freadline(FILE*);
int importFromFile(BinTree*);


#endif //LAB4A_CONTROLLER_H
