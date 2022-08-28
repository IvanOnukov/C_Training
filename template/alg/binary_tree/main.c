#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//typedef это псевдоним для конструкций языка
typedef enum {
    DECIMAL_ELEM,
    REAL_ELEM,
    STRING_ELEM,
} typeTree;

typedef union { // storage one of element
    int64_t decimal;
    double real;
    char *string; //like u_int8_t
} storeValueTree;

typedef struct TreeNode {
    struct {
        storeValueTree key;
        storeValueTree value;
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

extern struct Tree *newTree(typeTree key, typeTree value);

extern void freeTree(struct Tree *tree);

static void _freeTree(struct TreeNode *node);

extern storeValueTree getElemTree(struct Tree *tree, void *key);

static treeNode *_getElemTree(struct TreeNode *node, typeTree typeKey, void *key);

extern void setElemTree(struct Tree *tree, void *key, void *value);

extern void delElemTree(struct Tree *node, void *key);

extern _Bool elemInTree(struct Tree *node, void *key);

static void _printTree(struct TreeNode *node, typeTree key, typeTree value);

extern void printTree(struct Tree *root);

static void _printTreeAsList(struct TreeNode *node, typeTree key, typeTree value);

extern void printTreeAsList(struct Tree *root);

static treeNode *_newNode(typeTree typeKey, typeTree typeValue, void *key, void *value);

static void _setTree(struct TreeNode *node, typeTree typeKey, typeTree typeValue, void *key, void *value);

static void _setKey(treeNode *node, typeTree typeKey, void *key);

static void _setValue(treeNode *node, typeTree typeValue, void *value);


extern void *decimal(int64_t x);

extern void *string(char *x);

extern void *real(double *x);


int main() {

    struct Tree *tree = newTree(DECIMAL_ELEM, STRING_ELEM);

    setElemTree(tree, decimal(666), string("hcet"));
    setElemTree(tree, decimal(13), string("her"));
    setElemTree(tree, decimal(1), string("pes"));
    printTreeAsList(tree);

    storeValueTree dfd = getElemTree(tree, decimal(13));

    printf("%d\n", elemInTree(tree, decimal(1)));
    //  printf("%s\n", dfd.string);

    freeTree(tree);
    return 0;
}

extern void *decimal(int64_t x) {
    return (void *) x;
}

extern void *string(char *x) {
    return (void *) x;
}

extern void *real(double *x) {
    double *tmp = (double *) malloc(sizeof(double)); // надо освободить память
    return (void *) tmp;
}

extern struct Tree *newTree(typeTree key, typeTree value) {
    switch (key) {
        case DECIMAL_ELEM:
            break;
        case REAL_ELEM:
            break;
        case STRING_ELEM:
            break;
        default:
            fprintf(stderr, "%s\n", "key type don't supported.");
            return NULL;
    }
    switch (value) {
        case DECIMAL_ELEM:
            break;
        case REAL_ELEM:
            break;
        case STRING_ELEM:
            break;
        default:
            fprintf(stderr, "%s\n", "value type don't supported.");
            return NULL;
    }

    struct Tree *tree = (struct Tree *) malloc(sizeof(struct Tree));

    tree->type.key = key;
    tree->type.value = value;
    tree->node = NULL;
    return tree;
}

extern void setElemTree(struct Tree *tree, void *key, void *value) {
    if (tree->node == NULL) {
        tree->node = _newNode(tree->type.key, tree->type.value, key, value);
        return;
    }
    _setTree(tree->node, tree->type.key, tree->type.value, key, value);
}

static treeNode *_newNode(typeTree typeKey, typeTree typeValue, void *key, void *value) {
    treeNode *node = (treeNode *) malloc(sizeof(treeNode));
    _setKey(node, typeKey, key);
    _setValue(node, typeValue, value);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

static void _setTree(struct TreeNode *node, typeTree typeKey, typeTree typeValue, void *key, void *value) {
    int condition;
    switch (typeKey) {
        case DECIMAL_ELEM:
            if ((int64_t) key > node->data.key.decimal) {
                if (node->right == NULL) {
                    node->right = _newNode(typeKey, typeValue, key, value);
                    node->right->parent = node;
                    return;
                } else {
                    _setTree(node->right, typeKey, typeValue, key, value);
                }
            } else if ((int64_t) key < node->data.key.decimal) {
                if (node->left == NULL) {
                    node->left = _newNode(typeKey, typeValue, key, value);
                    node->left->parent = node;
                    return;
                } else {
                    _setTree(node->left, typeKey, typeValue, key, value);
                }
            } else {
                _setValue(node, typeValue, value);
            }
            break;
        case REAL_ELEM:
            if (*(double *) key > node->data.key.real) {
                if (node->right == NULL) {
                    node->right = _newNode(typeKey, typeValue, key, value);
                    node->right->parent = node;
                    return;
                } else {
                    _setTree(node->right, typeKey, typeValue, key, value);
                }
            } else if (*(double *) key < node->data.key.real) {
                if (node->left == NULL) {
                    node->left = _newNode(typeKey, typeValue, key, value);
                    node->left->parent = node;
                    return;
                } else {
                    _setTree(node->left, typeKey, typeValue, key, value);
                }
            } else {
                _setValue(node, typeValue, value);
            }
            break;
        case STRING_ELEM:
            condition = strcmp((char *) key, node->data.key.string);
            if (condition > 0) {
                if (node->right == NULL) {
                    node->right = _newNode(typeKey, typeValue, key, value);
                    node->right->parent = node;
                    return;
                } else {
                    _setTree(node->right, typeKey, typeValue, key, value);
                }
            } else if (condition < 0) {
                if (node->left == NULL) {
                    node->left = _newNode(typeKey, typeValue, key, value);
                    node->left->parent = node;
                    return;
                } else {
                    _setTree(node->left, typeKey, typeValue, key, value);
                }
            } else {
                _setValue(node, typeValue, value);
            }
            break;
    }
}

static void _setKey(treeNode *node, typeTree typeKey, void *key) {
    switch (typeKey) {
        case DECIMAL_ELEM:
            node->data.key.decimal = (int64_t) key;
            break;
        case REAL_ELEM:
            node->data.key.real = *(double *) key;
            free((double *) key);
            break;
        case STRING_ELEM:
            node->data.key.string = (char *) key;
            break;
    }
}

static void _setValue(treeNode *node, typeTree typeValue, void *value) {
    switch (typeValue) {
        case DECIMAL_ELEM:
            node->data.value.decimal = (int64_t) value;
            break;
        case REAL_ELEM:
            node->data.value.real = *(double *) value;
            free((double *) value);
            break;
        case STRING_ELEM:
            node->data.value.string = (char *) value;
            break;
    }
}

void printValue(struct TreeNode *node, typeTree typeValue) {
    switch (typeValue) {
        case DECIMAL_ELEM:
            printf("%ld] ", node->data.value.decimal);
            break;
        case REAL_ELEM:
            printf("%lf] ", node->data.value.real);
            break;
        case STRING_ELEM:
            printf("%s] ", node->data.value.string);
            break;
    }
}


static void _printTreeElem(struct TreeNode *node, typeTree key, typeTree value) {
    switch (key) {
        case DECIMAL_ELEM:
            printf("[%ld => ", node->data.key.decimal);
            printValue(node, value);
            break;
        case REAL_ELEM:
            printf("[%lf => ", node->data.key.real);
            printValue(node, value);
            break;
        case STRING_ELEM:
            printf("[%s => ", node->data.key.string);
            printValue(node, value);
            break;
    }
}

static void _printTreeAsList(struct TreeNode *node, typeTree key, typeTree value) {
    if (node == NULL) {
        return;
    }
    _printTreeAsList(node->left, key, value);
    _printTreeElem(node, key, value);
    _printTreeAsList(node->right, key, value);
}

static void _printTree(struct TreeNode *node, typeTree key, typeTree value) {
    if (node == NULL) {
        printf("NULL");
        return;
    }
    putchar('(');
    _printTree(node->left, key, value);
    _printTreeElem(node, key, value);
    _printTree(node->right, key, value);
    putchar(')');
}

extern void printTreeAsList(struct Tree *root) {
    printf("[");
    _printTreeAsList(root->node, root->type.key, root->type.value);
    printf("]\n");
}

extern void printTree(struct Tree *root) {
    _printTree(root->node, root->type.key, root->type.value);
    putchar('\n');
}

static void _freeTree(struct TreeNode *node) {
    if (node == NULL) {
        return;
    }
    _freeTree(node->left);
    _freeTree(node->right);
    free(node);
}

extern void freeTree(struct Tree *tree) {
    _freeTree(tree->node);
    free(tree);
}

extern storeValueTree getElemTree(struct Tree *tree, void *key) {
    struct TreeNode *node = _getElemTree(tree->node, tree->type.key, key);
    if (node == NULL) {
        fprintf(stderr, "%s\n", "value undefined");
        storeValueTree none;
        none.decimal = 0;
        return none;
    }
    return node->data.value;
}

static treeNode *_getElemTree(struct TreeNode *node, typeTree typeKey, void *key) {
    int condition;
    if (node == NULL) {
        return NULL;
    }
    switch (typeKey) {
        case DECIMAL_ELEM:
            if (((int64_t *) key) > node->data.key.decimal) {
                return _getElemTree(node->right, typeKey, key);
            } else if (((int64_t *) key) < node->data.key.decimal) {
                return _getElemTree(node->left, typeKey, key);
            }
            break;
        case REAL_ELEM:
            if (*(double *) key > node->data.key.decimal) {
                return _getElemTree(node->right, typeKey, key);
            } else if (*(double *) key < node->data.key.decimal) {
                return _getElemTree(node->left, typeKey, key);
            }
            break;
        case STRING_ELEM:
            condition = strcmp((char *) key, node->data.key.string);
            if (condition > 0) {
                return _getElemTree(node->right, typeKey, key);
            } else if (condition < 0) {
                return _getElemTree(node->left, typeKey, key);
            }
            break;
    }
    return node;
}


extern _Bool elemInTree(struct Tree *node, void *key) {
    return _getElemTree(node, node->type.key, key) != NULL;
}

//реализовать функцию добавления элимента в дерево +
//получить элимент дерева +
//задать элимент дерева +
//проверка на существования элимента в дереве
//реализовать функцию удоления элимента из дерева
//вывод элиментов дерева +

