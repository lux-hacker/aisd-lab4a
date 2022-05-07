#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "controller/controller.h"

BinTree* generateTree(int);
void timingAddElement();
void timingDeleteElement();
void timingDFS();
void timingFindElement();
void timingFindMinElement();

int main(){
   srand(time(NULL));
   printf("======[TIMING]======\n");
   printf("0)Exit\n");
   printf("1)Add element\n");
   printf("2)Delete element\n");
   printf("3)DFS\n");
   printf("4)Find element\n");
   printf("5)Find min element\n");
   printf("--> ");
   int n = getUInt();
   switch(n){
	case 1:{
	    timingAddElement();
	    break;
	}
	case 2:{
            timingDeleteElement();
            break;
        }
	case 3:{
            timingDFS();
            break;
        }
	case 4:{
            timingFindElement();
            break;
        }
	case 5:{
            timingFindMinElement();
            break;
        }
	default:{
	    break;
	}
   }
   return 0;
}

BinTree* generateTree(int size){
    FILE* buf = fopen("buf.bin", "w+b");
    BinTree* tree = (BinTree*) malloc(sizeof(BinTree));
    tree->root = NULL;
    for(int i = 0; i < size; i++){
	unsigned int key = rand() % size + 1;
	unsigned int data = key;
	fwrite(&key, sizeof(unsigned int), 1, buf);
	addNewElement(tree, key, data);
    }
    fclose(buf);
    return tree;
}

void timingAddElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for(int i = 1; i <= 10; i++){
	int size = 10000*i;
	double sum = 0;
	for(int j = 0; j < 10; j++){
	    BinTree* tree = generateTree(size);
	    unsigned int key = rand() % size + 1;
	    unsigned int data = key;
	    clock_t begin = clock();
	    addNewElement(tree, key, data);
	    clock_t end = clock();
	    sum += (double)(end-begin) / CLOCKS_PER_SEC;
	    freeTree(tree);
	    free(tree);
	}
	fprintf(fd, "%d,%f,%s\n", size, sum/10, "addElement");
    }
    fclose(fd);
}

void timingDeleteElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for(int i = 1; i <= 10; i++){
        int size = 10000*i;
        double sum = 0;
        for(int j = 0; j < 10; j++){
            BinTree* tree = generateTree(size);
            int offset = rand() % size;
	    FILE* buf = fopen("buf.bin", "r");
	    fseek(buf, offset * sizeof(unsigned int), SEEK_SET);
	    unsigned int key;
	    fread(&key, sizeof(unsigned int), 1, buf);
	    fclose(buf);
            clock_t begin = clock();
            deleteElement(tree, key);
            clock_t end = clock();
            sum += (double)(end-begin) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
	}                                                                                                                                    }
        fprintf(fd, "%d,%f,%s\n", size, sum/10, "deleteElement");
    }
    fclose(fd);
}

void timingDFS(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for(int i = 1; i <= 10; i++){
        int size = 10000*i;
	double sum = 0;
	for(int j = 0; j < 10; j++){
            BinTree* tree = generateTree(size);
            unsigned int from = rand() % size + 1;
            unsigned int to = rand() % (size - from) + from;
            clock_t begin = clock();
            Vector* vector = dfs(tree, from, to, NULL);
            clock_t end = clock();
            sum += (double)(end-begin) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
	    if(vector != NULL){
	        free(vector->data);
	        free(vector);
	    }
	}
	fprintf(fd, "%d,%f,%s\n", size, sum/10, "DFS");
    }
    fclose(fd);
}

void timingFindElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for(int i = 1; i <= 10; i++){
        int size = 10000*i;
        double sum = 0;
        for(int j = 0; j < 10; j++){
            BinTree* tree = generateTree(size);
            int offset = rand() % size;
            FILE* buf = fopen("buf.bin", "r");
            fseek(buf, offset * sizeof(unsigned int), SEEK_SET);
            unsigned int key;
            fread(&key, sizeof(unsigned int), 1, buf);
            fclose(buf);
            clock_t begin = clock();
            findByKey(tree, key, 1);
            clock_t end = clock();
            sum += (double)(end-begin) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
        }                                                                                                                                    }
        fprintf(fd, "%d,%f,%s\n", size, sum/10, "findElement");
    }
    fclose(fd);
}

void timingFindMinElement(){
    FILE* fd = fopen("timing.csv", "w+");
    fprintf(fd, "len,avg,func\n");
    for(int i = 1; i <= 10; i++){
	double sum = 0;
	int size = 100000*i;
	for(int j = 0; j < 10; j++){
            BinTree* tree = generateTree(size);
            clock_t begin = clock();
            findMin(tree, 1);
            clock_t end = clock();
            sum += (double)(end-begin) / CLOCKS_PER_SEC;
            freeTree(tree);
            free(tree);
	}
	fprintf(fd, "%d,%f,%s\n", size, sum/10, "findMinElement");
    }
    fclose(fd);
}
