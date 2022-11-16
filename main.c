#include <stdio.h>
#include <stdlib.h>
#include "dict.h"
#include "BTree.h"
#include "token.h"
#include "simplifytree.h"

static void printExprTree(FILE *fp, BTree *tree);

static void printExprTreeRec(FILE *fp, BTree *tree, BTNode *node);

static void printExprTree(FILE *fp, BTree *tree)
{
    // Check if the tree is empty
    if (tree == NULL)
        return;

    BTNode *root = btRoot(tree);
    if (root == NULL)
        return;

    printExprTreeRec(fp, tree, root);
    fprintf(fp, "\n");
}

static void printExprTreeRec(FILE *fp, BTree *tree, BTNode *node)
{
    Token *token = (Token *)btGetData(tree, node);
    TokenType type = tokenGetType(token);

    // Check if node is a number
    if (type == NUMBER)
    {
        double value = tokenGetNumber(token);
        fprintf(fp, "%.1lf", value);
        return;
    }

    // Check if node is a symbol
    if (type == SYMBOL)
    {
        char *sym = tokenGetSymbol(token);
        fprintf(fp, "%s", sym);
        return;
    }

    // Otherwise it is an operator
    char *op = tokenGetOperator(token);
    fprintf(fp, "(");
    printExprTreeRec(fp, tree, btLeft(tree, node));
    fprintf(fp, " %s ", op);
    printExprTreeRec(fp, tree, btRight(tree, node));
    fprintf(fp, ")");
}

int main()
{
    // Create the dictionary
    Dict *dict = dictCreate(1000);

    // Add the symbols
    double a = 1.0;
    double b = 2.0;
    double c = 3.0;
    double d = 4.0;
    dictInsert(dict, "a", (void *)&a);
    dictInsert(dict, "b", (void *)&b);
    dictInsert(dict, "c", (void *)&c);
    dictInsert(dict, "d", (void *)&d);

    // Create the expression tree
    BTree *tree = btCreate();

    BTNode *root = btCreateRoot(tree, (void *)tokenCreateOperator("+"));
    BTNode *l = btInsertLeft(tree, root, (void *)tokenCreateOperator("*"));
    BTNode *ll = btInsertLeft(tree, l, (void *)tokenCreateOperator("/"));
    btInsertLeft(tree, ll, (void *)tokenCreateSymbol("d"));
    btInsertRight(tree, ll, (void *)tokenCreateNumber(2.));
    BTNode *lr = btInsertRight(tree, l, (void *)tokenCreateOperator("-"));
    btInsertLeft(tree, lr, (void *)tokenCreateNumber(5.));
    btInsertRight(tree, lr, (void *)tokenCreateSymbol("x"));
    BTNode *r = btInsertRight(tree, root, (void *)tokenCreateOperator("+"));
    BTNode *rl = btInsertLeft(tree, r, (void *)tokenCreateOperator("-"));
    btInsertLeft(tree, rl, (void *)tokenCreateSymbol("c"));
    btInsertRight(tree, rl, (void *)tokenCreateSymbol("a"));
    BTNode *rr = btInsertRight(tree, r, (void *)tokenCreateOperator("*"));
    btInsertLeft(tree, rr, (void *)tokenCreateSymbol("b"));
    btInsertRight(tree, rr, (void *)tokenCreateNumber(3.));

    // (((d / 2) * (5 - x)) + ((c - a) + (b * 3)))
    printExprTree(stdout, tree);

    simplifyExprTree(tree, dict);

    // ((2 * (5 - x)) + 8)
    printExprTree(stdout, tree);

    btFree(tree);
    dictFree(dict);
    tokenFreeAll();
}
