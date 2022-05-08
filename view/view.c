#include "view.h"

void showTrunks(Trunk*);

void printMenu(){
    printf("======[WELCOME TO THE MENU]======\n");
    printf("0)Exit program\n");
    printf("1)Add new element\n");
    printf("2)Delete element\n");
    printf("3)Search in tree\n");
    printf("4)Find element\n");
    printf("5)Find min element\n");
    printf("6)Print tree\n");
    printf("7)Import tree from file\n");
    printf("--> ");
}

void showTrunks(Trunk *p) {
    if (p == NULL) {
        return;
    }
    showTrunks(p->prev);
    printf("%s", p->str);
}

void printTree(BinTreeNode* root, Trunk* prev, int isLeft){
    if(root == NULL) return;
    char* prev_str = "    ";
    Trunk trunk = {prev, prev_str};
    printTree(root->right, &trunk, 1);
    if(!prev){
        trunk.str = "---";
    } else if(isLeft){
        trunk.str = ".---";
        prev_str = "   |";
    } else {
        trunk.str = "`---";
        prev->str = prev_str;
    }

    showTrunks(&trunk);
    printf(" (%d,%d)\n", root->key, root->data);
    if(prev){
        prev->str = prev_str;
    }
    trunk.str = "    |";
    printTree(root->left, &trunk, 0);
}

void printVector(Vector* vector){
    for(int i = 0; i < vector->size; i++){
        printf("%d; ", vector->data[i]);
    }
    printf("\n");
}
