#include "BinTree.h"
#include "stdlib.h"

BinTreeNode* nextElement(BinTreeNode*);
BinTreeNode* minElement(BinTreeNode*);

Vector* dfs(BinTree* tree, unsigned int from, unsigned int to, Vector* vector){
    Vector* answer = vector;
    if(tree == NULL) return answer;
    BinTreeNode* ptr = tree->root;
    if(ptr == NULL) return answer;
    BinTree left = {ptr->left}, right = {ptr->right};
    answer = dfs(&right, from, to, answer);
    if(ptr->key < from || ptr->key > to){
        if(answer == NULL){
            answer = (Vector*) malloc(sizeof(Vector));
            answer->size = 1;
            answer->data = (unsigned int*) malloc(sizeof(unsigned int));
            answer->data[0] = ptr->data;
        } else {
            answer->size++;
            answer->data = (unsigned int*) realloc(answer->data, answer->size * sizeof(unsigned int));
            answer->data[answer->size - 1] = ptr->data;
        }
    }
    answer = dfs(&left, from, to, answer);
    return answer;
}

BinTreeNode* findByKey(BinTree* tree, unsigned int key, unsigned int order){
    if(tree == NULL || tree->root == NULL) return NULL;
    BinTreeNode* ptr = tree->root;
    while(ptr != NULL){
        if(ptr->key == key){
            int i = 1;
            while(ptr != NULL && i != order && ptr->key == key){
                i++;
                ptr = ptr->left;
            }
            if(i != order || ptr == NULL) return NULL;
            if(ptr->key != key) return NULL;
            return ptr;
        } else {
            if(key < ptr->key) ptr = ptr->left;
            else ptr = ptr->right;
        }
    }
    return NULL;
}

BinTreeNode* findMin(BinTree* tree, unsigned int order){
    if(tree == NULL || tree->root == NULL) return NULL;
    BinTreeNode* ptr = tree->root;
    while(ptr->left != NULL){
        ptr = ptr->left;
    }
    while(ptr->parent != NULL && ptr->key == ptr->parent->key) ptr = ptr->parent;
    int i = 1;
    while(i != order && ptr->left != NULL){
        i++;
        ptr = ptr->left;
    }
    if(i != order) return NULL;
    return ptr;
}

void addNewElement(BinTree* tree, unsigned int data, unsigned int key){
    if(tree->root == NULL){
        tree->root = (BinTreeNode*) malloc(sizeof(BinTreeNode));
        tree->root->key = key;
        tree->root->data = data;
        tree->root->parent = NULL;
        tree->root->left = NULL;
        tree->root->right = NULL;
        tree->root->release = 0;
        return;
    }
    int duplicate = 0;
    BinTreeNode* ptr = tree->root;
    BinTreeNode* par = tree->root->parent;
    while(ptr != NULL && duplicate != 1){
        par = ptr;
        if(key < ptr->key){
            ptr = ptr->left;
        } else if (key > ptr->key) {
            ptr = ptr->right;
        } else {
            duplicate = 1;
            ptr = ptr->left;
        }
    }

    if(duplicate == 0){
        if(key < par->key){
            par->left = (BinTreeNode*) malloc(sizeof(BinTreeNode));
            ptr = par->left;
        } else {
            par->right = (BinTreeNode*) malloc(sizeof(BinTreeNode));
            ptr = par->right;
        }
        ptr->parent = par;
        ptr->key = key;
        ptr->data = data;
        ptr->left = NULL;
        ptr->right = NULL;
        ptr->release = 0;
    } else {
        while(ptr != NULL && ptr->key == key) {
            par = ptr;
            ptr = ptr->left;
        }
        if(ptr == NULL){
            par->left = (BinTreeNode*) malloc(sizeof(BinTreeNode));
            ptr = par->left;
            ptr->parent = par;
            ptr->key = key;
            ptr->data = data;
            ptr->left = NULL;
            ptr->right = NULL;
            ptr->release = par->release + 1;
        } else {
            BinTreeNode* node = (BinTreeNode*) malloc(sizeof(BinTreeNode));
            node->parent = par;
            node->left = ptr;
            node->key = key;
            node->data = data;
            node->right = NULL;
            ptr->parent = node;
            par->left = node;
            node->release = par->release + 1;
        }
    }
}

int deleteElement(BinTree* tree, unsigned int key){
    BinTreeNode* ptr = tree->root;
    while(ptr != NULL && ptr->key != key){
        if(key > ptr->key) ptr = ptr->right;
        else ptr = ptr->left;
    }
    if(ptr == NULL) return 1;
    if(ptr->left != NULL && ptr->key == ptr->left->key){
        if(ptr == tree->root){
            tree->root = tree->root->left;
            tree->root->right = ptr->right;
            tree->root->parent = NULL;
            ptr->right->parent = tree->root;
            free(ptr);
        } else {
            ptr->left->parent = ptr->parent;
            if(ptr->parent->left == ptr) ptr->parent->left = ptr->left;
            else ptr->parent->right = ptr->left;
            if(ptr->right != NULL){
                ptr->left->right = ptr->right;
                ptr->right->parent = ptr->left;
            }
            free(ptr);
        }
    } else {
        if(ptr->left == NULL && ptr->right == NULL){
            if(ptr->parent == NULL){
                free(ptr);
                tree->root = NULL;
            } else {
                if(ptr->parent->left == ptr) ptr->parent->left = NULL;
                else ptr->parent->right = NULL;
                free(ptr);
            }
        } else if(ptr->left == NULL){
            if(ptr->parent == NULL){
                tree->root = tree->root->right;
                tree->root->parent = NULL;
                free(ptr);
            } else {
                if(ptr->parent->left == ptr) ptr->parent->left = ptr->right;
                else ptr->parent->right = ptr->right;
                free(ptr);
            }
        } else if(ptr->right == NULL){
            if(ptr->parent == NULL){
                tree->root = tree->root->left;
                tree->root->parent = NULL;
                free(ptr);
            } else {
                if(ptr->parent->left == ptr) ptr->parent->left = ptr->left;
                else ptr->parent->right = ptr->left;
                free(ptr);
            }
        } else {
            BinTreeNode* next = nextElement(ptr);
            int next_key = next->key, next_data = next->data;
            deleteElement(tree, next_key);
            ptr->key = next_key;
            ptr->data = next_data;
        }
    }
    return 0;
}

BinTreeNode* nextElement(BinTreeNode* root){
    if(root->right != NULL){
        return minElement(root->right);
    } else {
        BinTreeNode* ptr = root;
        BinTreeNode* par = ptr->parent;
        while(par != NULL && par->right == ptr){
            ptr = par;
            par = ptr->parent;
        }
        return ptr;
    }
}

BinTreeNode* minElement(BinTreeNode* root){
    while(root->left != NULL) root = root->left;
    return root;
}

void freeTree(BinTree* tree){
    if(tree->root == NULL) return;
    if(tree->root->left == NULL && tree->root->right == NULL){
        free(tree->root);
        return;
    }
    BinTree left = {tree->root->left}, right = {tree->root->right};
    freeTree(&left);
    freeTree(&right);
    free(tree->root);
}
