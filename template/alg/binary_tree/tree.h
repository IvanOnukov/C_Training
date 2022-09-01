#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    DECIMAL_ELEM,
    REAL_ELEM,
    STRING_ELEM,
} typeTree;

typedef union { // storage one of element
    int64_t decimal;
    double real;
    char *string;
} storeValueType;

typedef struct TreeNode {
    struct {
        storeValueType key;
        storeValueType value;
    } data;
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent;
} treeNode;

typedef struct Tree {
    struct {
        typeTree key;
        typeTree value;
    } type;
    struct TreeNode *node;
} Tree;

extern void *decimal(int64_t x);

extern void *string(char *x);

extern void *real(double *x);


extern struct Tree *newTree(typeTree key, typeTree value);

extern storeValueType getElemTree(struct Tree *tree, void *key);

extern void setElemTree(struct Tree *tree, void *key, void *value);

extern void delElemTree(struct Tree *node, void *key);

extern _Bool elemInTree(struct Tree *tree, void *key);

extern void printTree(struct Tree *root);

extern void printTreeAsList(struct Tree *root);

extern void freeTree(struct Tree *tree);


static treeNode *_newNode(typeTree typeKey, typeTree typeValue, void *key, void *value);

static void _setTree(struct TreeNode *node, typeTree typeKey, typeTree typeValue, void *key, void *value);

static void _setKey(treeNode *node, typeTree typeKey, void *key);

static void _setValue(treeNode *node, typeTree typeValue, void *value);

static void _printTree(struct TreeNode *node, typeTree key, typeTree value);

static void _printTreeAsList(struct TreeNode *node, typeTree key, typeTree value);

static treeNode *_getElemTree(struct TreeNode *node, typeTree typeKey, void *key);

static treeNode *_delList(struct Tree *tree, typeTree typeKey, void *key);

static void _delHalfList(struct Tree *tree, treeNode *node);

static void _delNotList(treeNode *node);

static void _freeTree(struct TreeNode *node);
