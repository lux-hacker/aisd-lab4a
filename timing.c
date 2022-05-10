#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "controller/controller.h"

BinTree *generateTree(int);
void timingAddElement();
void timingDeleteElement();
void timingFindElement();

int main() {
    srand(time(NULL));
    printf("======[TIMING]======\n");
    printf("0)Exit\n");
    printf("1)Add element\n");
    printf("2)Delete element\n");
    printf("3)Find element\n");
    printf("--> ");
    int n = getUInt();
    switch (n) {
        case 1: {
            timingAddElement();
            break;
        }
        case 2: {
            timingDeleteElement();
            break;
        }
        case 3: {
            timingFindElement();
            break;
        }
        default: {
            break;
        }
    }
    return 0;
}

BinTree *generateTree(int size) {
    FILE *buf = fopen("buf.bin", "w+b");
    BinTree *tree = (BinTree *) malloc(sizeof(BinTree));
    tree->root = NULL;
    for (int i = 0; i < size; i++) {
        unsigned int key = rand();
        unsigned int data = key;
        fwrite(&key, sizeof(unsigned int), 1, buf);
        addNewElement(tree, key, data);
    }
    fclose(buf);
    return tree;
}

void timingAddElement() {
    FILE *fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for (int size = 100000; size <= 5000000; size += 100000) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            BinTree *tree = generateTree(size);
            unsigned int keys[100] = {0};
            for (int i = 0; i < 100; i++) {
                keys[i] = rand();
            }
            clock_t start = clock();
            for (int i = 0; i < 100; i++) {
                addNewElement(tree, keys[i], keys[i]);
            }
            clock_t end = clock();
            sum += (double) (end - start) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }
        fprintf(fd, "%d,%f,%s\n", size, sum / 10, "addElement");
    }
    fclose(fd);
}

void timingDeleteElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for (int size = 100000; size <= 5000000; size += 100000) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            BinTree *tree = generateTree(size);
            unsigned int keys[100] = {0};
            for (int i = 0; i < 100; i++) {
                keys[i] = rand();
            }
            clock_t start = clock();
            for (int i = 0; i < 100; i++) {
                deleteElement(tree, keys[i]);
            }
            clock_t end = clock();
            sum += (double) (end - start) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }
        fprintf(fd, "%d,%f,%s\n", size, sum / 10, "addElement");
    }
    fclose(fd);
}

void timingFindElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for (int size = 100000; size <= 5000000; size += 100000) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            BinTree *tree = generateTree(size);
            unsigned int keys[100] = {0};
            for (int i = 0; i < 100; i++) {
                keys[i] = rand();
            }
            clock_t start = clock();
            for (int i = 0; i < 100; i++) {
                findByKey(tree, keys[i], 1);
            }
            clock_t end = clock();
            sum += (double) (end - start) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }
        fprintf(fd, "%d,%f,%s\n", size, sum / 10, "addElement");
    }
    fclose(fd);
}
