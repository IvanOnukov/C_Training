#pragma once
#include "tree.h"

int main() {

    struct Tree *tree = newTree(DECIMAL_ELEM, STRING_ELEM);

    setElemTree(tree, decimal(50), string("A"));
    setElemTree(tree, decimal(40), string("B"));
    setElemTree(tree, decimal(60), string("C"));
    setElemTree(tree, decimal(70), string("D"));
    setElemTree(tree, decimal(55), string("E"));
    printTreeAsList(tree);
    delElemTree(tree, decimal(60));
    printTreeAsList(tree);

    storeValueTree dfd = getElemTree(tree, decimal(55));
    printf("%s\n", dfd.string);

    printf("%d\n", elemInTree(tree->node, decimal(70)));

    freeTree(tree);
    return 0;
}
