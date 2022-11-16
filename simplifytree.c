
#include "BTree.h"
#include "token.h"
#include "dict.h"

#include "simplifytree.h"

// Assume well-formed expressions tree

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
    if(!btIsRoot(tree, node))
    {
        BTNode *parentGauche = btLeft(tree, btParent(tree, node));
        BTNode *parentDroite = btRight(tree, btParent(tree, node));
        if(tokenGetType((Token *)btGetData(tree, parentGauche)) == NUMBER && tokenGetType((Token *)btGetData(tree, parentDroite)) == NUMBER)
        {
            double nb1 = tokenGetNumber((Token *)btGetData(tree, parentGauche));
            double nb2 = tokenGetNumber((Token *)btGetData(tree, parentDroite));
        }
    }
}
void simplifyExprTree(BTree *tree, Dict *dict)
{
    compute(tree, btRoot(tree), dict);
}