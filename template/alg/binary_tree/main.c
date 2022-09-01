#include "tree.h"

typedef struct HashTab {
    struct {
        typeTree key;
        typeTree value;
    } type;
    size_t size;
    Tree **table;
} HashTab;

extern HashTab *newHashTab(size_t size, typeTree key, typeTree value);

extern void freeHashTab(HashTab *hashTab);

extern storeValueType getHashTab(HashTab *hashTab, void *key);

extern void setInHashTab(HashTab *hashTab, void *key, void *value);

extern void delElemHashTab(HashTab *hashTab, void *key);

extern _Bool inHashTab(HashTab *hashTab, void *key);

extern void printHashTab(HashTab *hashTab);

static uint32_t _strHash(char *str, size_t size);

extern uint32_t genHash(HashTab *hashTab, void *key);


int main() {

    HashTab *tab = newHashTab(5000, STRING_ELEM, DECIMAL_ELEM);
    setInHashTab(tab, string("word"), decimal(333));
    setInHashTab(tab, string("car"), decimal(555));
    setInHashTab(tab, string("table"), decimal(111));
    setInHashTab(tab, string("watch"), decimal(423));

    char *testVal1 = "car";
    char *testVal2 = "dog";


    printHashTab(tab);
    int64_t value = getHashTab(tab, string(testVal1)).decimal;
    printf("get value - %ld by key %s\n", value, testVal1);

    char *ask = "there is a key in this table";
    char *y = "yes";
    char *n = "no";


    printf("%s - [%s] - %s\n", ask, testVal1,  inHashTab(tab, string(testVal1)) ? y : n);
    printf("%s - [%s] - %s\n", ask, testVal2,  inHashTab(tab, string(testVal2)) ? y : n);
    delElemHashTab(tab, string(testVal1));
    printf("%s - [%s] - %s\n", ask, testVal1,  inHashTab(tab, string(testVal1)) ? y : n);
    printHashTab(tab);

    freeHashTab(tab);
//    struct Tree *tree = newTree(DECIMAL_ELEM, STRING_ELEM);
//
//    setElemTree(tree, decimal(50), string("A"));
//    setElemTree(tree, decimal(40), string("B"));
//    setElemTree(tree, decimal(60), string("C"));
//    setElemTree(tree, decimal(70), string("D"));
//    setElemTree(tree, decimal(55), string("E"));
//    printTreeAsList(tree);
//    delElemTree(tree, decimal(50));
//    printTreeAsList(tree);

//    storeValueType dfd = getElemTree(tree, decimal(55));
//    printf(%sn, dfd.string);
//
//    printf(%dn, elemInTree(tree->node, decimal(70)));

//    freeTree(tree);
    return 0;
}


extern HashTab *newHashTab(size_t size, typeTree key, typeTree value) {
    switch (key) {
        case DECIMAL_ELEM:
        case STRING_ELEM:
            break;
        default:
            fprintf(stderr, "%s\n", "key type not supported");
            return NULL;
    }
    switch (value) {
        case DECIMAL_ELEM:
        case REAL_ELEM:
        case STRING_ELEM:
            break;
        default:
            fprintf(stderr, "%s\n", "value type not supported");
            return NULL;
    }
    HashTab *hashTab = (HashTab *) malloc(sizeof(HashTab));
    hashTab->table = (Tree **) malloc(sizeof(Tree) * size);
    for (size_t i = 0; i < size; ++i) {
        hashTab->table[i] = newTree(key, value);
    }
    hashTab->size = size;
    hashTab->type.key = key;
    hashTab->type.value = value;
    return hashTab;
}

extern void freeHashTab(HashTab *hashTab) {
    for (int i = 0; i < hashTab->size; ++i) {
        freeTree(hashTab->table[i]);
    }
    free(hashTab->table);
    free(hashTab);
}

extern void printHashTab(HashTab *hashTab) {
    printf("{\n");
    for (int i = 0; i < hashTab->size; ++i) {
        if (hashTab->table[i]->node == NULL) {
            continue;
        }
        uint32_t hash;
        switch (hashTab->type.key) {
            case DECIMAL_ELEM:
                hash = hashTab->table[i]->node->data.key.decimal % hashTab->size;
                break;
            case STRING_ELEM:
                hash = _strHash(hashTab->table[i]->node->data.key.string, hashTab->size);
                break;

        }
        printf("\t%d", hash);
        printTreeAsList(hashTab->table[i]);
    }
    printf("}\n");
}

extern uint32_t genHash(HashTab *hashTab, void *key) {
    uint32_t hash = 0;
    switch (hashTab->type.key) {
        case DECIMAL_ELEM:
            hash = (uint64_t) key % hashTab->size;
            break;
        case STRING_ELEM:
            hash = _strHash((char *) key, hashTab->size);
            break;
    }
    return hash;
}

extern void setInHashTab(HashTab *hashTab, void *key, void *value) {
    uint32_t hash = genHash(hashTab, key);
    setElemTree(hashTab->table[hash], key, value);
}

static uint32_t _strHash(char *str, size_t size) {
    uint32_t hash;
    for (hash = 0; *str != '\0'; ++str) {
        hash = *str + 31 * hash;
    }
    return hash % size;
}


extern storeValueType getHashTab(HashTab *hashTab, void *key) {
    uint32_t hash = genHash(hashTab, key);
    storeValueType result = getElemTree(hashTab->table[hash], key);
    return result;
}

extern _Bool inHashTab(HashTab *hashTab, void *key) {
    uint32_t hash = genHash(hashTab, key);
    _Bool result = elemInTree(hashTab->table[hash], key);
    return result;

}

extern void delElemHashTab(HashTab *hashTab, void *key) {
    uint32_t hash = genHash(hashTab, key);
//    switch(hashTab->type.key) {
//        case DECIMAL_ELEM:
//            hash = (uint64_t)key % hashTab->size;
//            break;
//        case STRING_ELEM:
//            hash = _strHash((uint8_t*)key, hashTab->size);
//            break;
//    }
    delElemTree(hashTab->table[hash], key);
}