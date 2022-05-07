#include "controller.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>


unsigned int getUInt(){
    char *msg = "";
    while (1) {
        printf("%s", msg);
        char *input = readline("");
        msg = "======[MUST BE NUMBER]======\n--> ";
        char *ptr;
        int value = (int) strtol(input, &ptr, 10);
        if (strlen(input) != 0 && ptr == input + strlen(input)) {
            free(input);
            if(value < 0){
                msg = "======[NEGATIVE NUMBER ISN'T ALLOWED]======\n--> ";
                continue;
            }
            return value;
        }
        free(input);
    }
}

void menu(){
    BinTree* tree = (BinTree*) malloc(sizeof(BinTree));
    tree->root = NULL;
    while(1){
        printMenu();
        unsigned int n = getUInt();
        switch (n) {
            case 0:{
                freeTree(tree);
                free(tree);
                return;
            }
            case 1:{
                printf("======[ADD ELEMENT]======\n");
                printf("Enter key\n--> ");
                unsigned int key = getUInt();
                printf("Enter data\n--> ");
                unsigned int data = getUInt();
                addNewElement(tree, key, data);
                break;
            }
            case 2:{
                printf("======[DELETE ELEMENT]======\n");
                printf("Enter key\n--> ");
                unsigned int key = getUInt();
                int err = deleteElement(tree, key);
                if(err == 1){
                    printf("======[ERROR]======\n");
                    printf("Element with this key doesn't exist\n");
                }
                break;
            }
            case 3:{
                printf("======[SEARCH IN TREE]======\n");
                printf("Enter key from\n--> ");
                unsigned int from = getUInt();
                printf("Enter key to\n--> ");
                unsigned int to = getUInt();
                Vector* answer = dfs(tree, from, to, NULL);
                if(answer == NULL){
                    printf("======[ERROR]======\n");
                    printf("Keys outside this range don't exist\n");
                } else {
                    printVector(answer);
                    free(answer->data);
                    free(answer);
                }
                break;
            }
            case 4:{
                printf("======[FIND ELEMENT]======\n");
                printf("Enter key\n--> ");
                unsigned int key = getUInt();
                printf("Enter order\n--> ");
                unsigned int order = getUInt();
                BinTreeNode* ptr = findByKey(tree, key, order);
                if(ptr == NULL){
                    printf("======[ERROR]======\n");
                    printf("Element with this key or order doesn't exist\n");
                } else {
                    printf("ANSWER: %d - %d\n", ptr->key, ptr->data);
                }
                break;
            }
            case 5:{
                printf("======[FIND MIN ELEMENT]======\n");
                printf("Enter order\n--> ");
                unsigned int order = getUInt();
                BinTreeNode* ptr = findMin(tree, order);
                if(ptr == NULL){
                    printf("======[ERROR]======\n");
                    printf("Min element with order doesn't exist\n");
                } else {
                    printf("ANSWER: %d - %d\n", ptr->key, ptr->data);
                }
                break;
            }
            case 6:{
                printf("======[OUTPUT TREE]======\n");
                if(tree->root == NULL){
                    printf("======[ERROR]======\n");
                    printf("Tree is empty\n");
                } else {
                    printTree(tree->root, NULL, 0);
                }
                break;
            }
            case 7:{
                freeTree(tree);
                int err = importFromFile(tree);
                if(err == 1){
                    printf("======[ERROR]======\n");
                    printf("This file doesn't exist\n");
                } else if (err == 2){
                    printf("======[ERROR]======\n");
                    printf("Data in file is incorrect\n");
                } else if (err == 3){
                    printf("======[ERROR]======\n");
                    printf("File name shouldn't be empty\n");
                }
            }
            default:{
                printf("======[ERROR]======\n");
                printf("This menu point doesn't exist\n");
            }
        }
    }
}

char* freadline(FILE* fd){
    char buf[80] = {0};
    char* res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = fscanf(fd, "%80[^\n]", buf);
        if(n < 0){
            if(!res) return NULL;
        } else if(n > 0){
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = (char*) realloc(res, (str_len + 1)* sizeof(char));
            memcpy(res + len, buf, chunk_len);
            len = str_len;
            res[str_len] = '\0';
        } else {
            fscanf(fd, "%*c");
        }
    } while(n > 0);

    if(len > 0){
        res[len] = '\0';
    } else {
        res = (char*) calloc(1, sizeof(char));
    }
    return res;
}

int importFromFile(BinTree* tree){
    printf("======[IMPORT FROM FILE]======\n");
    char* filename = readline("Enter file name\n--> ");
    if(filename == NULL || strlen(filename) < 1) return 3;
    FILE* fd = fopen(filename, "r");
    if(fd == NULL){
        free(filename);
        return 1;
    }
    while(!feof(fd)){
        char* str_key = freadline(fd);
        char* str_data = freadline(fd);
        if(str_key){
            if(str_data){
                char* ptr = NULL;
                unsigned int key = strtoul(str_key, &ptr, 10);
                if(strlen(str_key) < 1 && ptr != str_key + strlen(str_key)){
                    free(str_data);
                    free(str_key);
		    fclose(fd);
	            free(filename);
                    return 2;
                }
                ptr = NULL;
                unsigned int data = strtoul(str_data, &ptr, 10);
                if(strlen(str_data) < 1 && ptr != str_data + strlen(str_data)){
                    free(str_data);
                    free(str_key);
		    fclose(fd);
		    free(filename);
                    return 2;
                }
                addNewElement(tree, data, key);
                free(str_data);
                free(str_key);
            } else {
                free(str_data);
		fclose(fd);
		free(filename);
                return 2;
            }
        } else {
	    fclose(fd);
	    free(filename);
            return 2;
        }
    }
    fclose(fd);
    free(filename);
    return 0;
}

