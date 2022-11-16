#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"
#include "BTree.c"
#include "token.h"
#include "token.c"
#include "dict.h"
#include "simplifytree.h"

BTNode *findLeave(BTree *tree,BTNode *node) //semble marcher
{
  if(!btIsExternal(tree, node))
    return findLeave(tree, node->right);
  else 
    return node; 
}
BTNode *findSiblings(BTree *tree, BTNode *node)
{
  return btParent(tree, node)->left;
}
// On sait que chaque noeud contient un token il faut donc obtenir son type.
void simplifyExprTree(BTree *tree, Dict *dict)
{
 //Initialisation des feuilles et du parent associé. 
 BTNode *leaveRight = findLeave(tree, tree->root);
 BTNode *leaveLeft = findSiblings(tree,leaveRight);
 BTNode *parent = btParent(tree, leaveRight);
double opRight = 0;

 if(tokenGetType((Token *)leaveRight->data) == NUMBER)
    opRight = tokenGetNumber((Token *)leaveRight->data);

  else if(tokenGetType((Token *)leaveRight->data) == SYMBOL)
    {
      char *key = tokenGetSymbol((Token *)leaveRight->data);
    }
  

}



int main(int argc, char const *argv[])
{
    BTree *tree = btCreate();
    int a = 5; 
    int e = 10;
    int* b = &a; 
    int* d = &e;
    int* f = &a; 
    btCreateRoot(tree, (int *)b);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)d);
    btInsertRight(tree,tree->root,(int *)f);

    //printf("%d \n", *b);
    //printf("root : %d \n", tree->root[0]);
    //printf("%d \n", btIsExternal(tree, tree->root->right)); // ok 
    //printf("%d \n", *(int *)btGetData(tree,tree->root)); //accède à la valeur d'un des noeuds (ici la racine en l'occurence).
    printf("value of the leave %d \n", *(int *)btGetData(tree, findLeave(tree, tree->root)));

    return 0;
}
