#include "view.h"
#include <stdio.h>
#include <stdlib.h>

void showTrunks(Trunk*);
void _treeToPNG(BinTreeNode*, FILE*);

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
    printf("8)Tree to PNG\n");
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
    char* prev_str = "     ";
    Trunk trunk = {prev, prev_str};
    printTree(root->right, &trunk, 1);
    if(!prev){
        trunk.str = "----";
    } else if(isLeft){
        trunk.str = ".----";
        prev_str = "    |";
    } else {
        trunk.str = "`----";
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

void treeToPNG(BinTree* tree, const char* fn){
    FILE* fd = fopen("buf.dot", "w");
    fprintf(fd, "digraph G{\n");
    BinTreeNode* pnt = tree->root;
    if(pnt == NULL){
        fprintf(fd, "\n");
    } else if(pnt->left == NULL && pnt->right == NULL){
        fprintf(fd, "   (%d,%d);\n", pnt->key, pnt->data);
    } else {
        _treeToPNG(pnt, fd);
    }
    fprintf(fd, "}");
    fclose(fd);
    char cmd[255] = {0};
    sprintf(cmd, "dot -Tpng buf.dot -o %s", fn);
    system(cmd);
}

void _treeToPNG(BinTreeNode* root, FILE* fd){
    static int nil = 0;
    if(root->left != NULL) {
        printf("LOG: GRAPHVIZ:key - %d release - %d\n",root->key, root->release);
        fprintf(fd, "   u_%d_%d -> u_%d_%d;\n", root->key, root->release, root->left->key, root->left->release);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\"];\n", root->key, root->release, root->key, root->data);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\"];\n", root->left->key, root->left->release, root->left->key, root->left->data);
        _treeToPNG(root->left, fd);
    } else {
        printf("LOG: GRAPHVIZ:key - %d release - %d\n",root->key, root->release);
        fprintf(fd, "   null%d [shape=point];\n", nil);
        fprintf(fd, "   u_%d_%d -> null%d;\n",root->key, root->release, nil);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\"];\n", root->key, root->release, root->key, root->data);
        nil++;
    }
    if(root->right != NULL){
        printf("LOG: GRAPHVIZ:key - %d release - %d\n",root->key, root->release);
        fprintf(fd, "   u_%d_%d -> u_%d_%d;\n", root->key, root->release, root->right->key, root->right->release);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\"];\n", root->key, root->release, root->key, root->data);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\"];\n", root->right->key, root->right->release, root->right->key, root->right->data);
        _treeToPNG(root->right, fd);
    } else {
        printf("LOG: GRAPHVIZ:key - %d release - %d\n",root->key, root->release);
        fprintf(fd, "   null%d [shape=point];\n", nil);
        fprintf(fd, "   u_%d_%d -> null%d;\n",root->key, root->release, nil);
        fprintf(fd, "   u_%d_%d [label=\"(%d,%d)\"];\n", root->key, root->release, root->key, root->data);
        nil++;
    }
}
