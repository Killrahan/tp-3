#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "token.h"
#include "dict.h"
#include "simplifytree.h"
#include <BTree.c>
#include <token.c>
#include <dict.c>
static void compute(BTree *tree, BTNode *node, Dict *dict)
{
    if(tokenGetType((Token *)btGetData(tree, node)) == OPERATOR) 
    {
        compute(tree, btLeft(tree, node), dict);
        compute(tree, btRight(tree, node), dict);
    }
    else if(tokenGetType((Token *)btGetData(tree, node)) == SYMBOL)
    {
        if(dictContains(dict, tokenGetSymbol((Token *)btGetData(tree, node))))
        {
            btSetData(tree, node, (Token *)dictSearch(dict, tokenGetSymbol((Token *)btGetData(tree, node))));
        }
    }
}
void simplifyExprTree(BTree *tree, Dict *dict)
{
    compute(tree, btRoot(tree), dict);
}
int main(int argc, char const *argv[])
{
    
    return 0;
}
