#include <stdlib.h>
#include <stdio.h>

#include "token.h"

typedef struct _tokenNode TokenNode;

struct _token
{
    TokenType type;
    union
    {
        double num;
        char *op;
        char *sym;
    } value;
};

struct _tokenNode
{
    TokenNode *next;
    Token *token;
};

static TokenNode *tokensList = NULL;

static void addNewToken(Token *token);

static void addNewToken(Token *token)
{
    TokenNode *newNode = malloc(sizeof(TokenNode));
    newNode->token = token;
    newNode->next = tokensList;
    tokensList = newNode;
}

Token *tokenCreateNumber(double num)
{
    Token *t = malloc(sizeof(Token));
    if (!t)
    {
        fprintf(stderr, "Error in tokenCreateNumber: Could not allocate memory.\n");
        exit(1);
    }

    addNewToken(t);

    t->type = NUMBER;
    t->value.num = num;
    return t;
}

Token *tokenCreateOperator(char *op)
{
    Token *t = malloc(sizeof(Token));
    if (!t)
    {
        fprintf(stderr, "Error in tokenCreateOperator: Could not allocate memory.\n");
        exit(1);
    }

    addNewToken(t);

    t->type = OPERATOR;
    t->value.op = op;
    return t;
}

Token *tokenCreateSymbol(char *sym)
{
    Token *t = malloc(sizeof(Token));
    if (!t)
    {
        fprintf(stderr, "Error tokenCreateSymbol: Could not allocate memory.\n");
        exit(1);
    }

    addNewToken(t);

    t->type = SYMBOL;
    t->value.sym = sym;
    return t;
}

TokenType tokenGetType(Token *token)
{
    return token->type;
}

double tokenGetNumber(Token *token)
{
    if (token->type != NUMBER)
    {
        fprintf(stderr, "Error in tokenGetNumber: Token is not a number.\n");
        exit(1);
    }

    return token->value.num;
}

char *tokenGetOperator(Token *token)
{
    if (token->type != OPERATOR)
    {
        fprintf(stderr, "Error in tokenGetOperator: Token is not an operator.\n");
        exit(1);
    }

    return token->value.op;
}

char *tokenGetSymbol(Token *token)
{
    if (token->type != SYMBOL)
    {
        fprintf(stderr, "Error in tokenGetSymbol: Token is not an symbol.\n");
        exit(1);
    }

    return token->value.sym;
}

void tokenFreeAll()
{
    TokenNode *current = tokensList;
    while (current)
    {
        TokenNode *next = current->next;
        free(current->token);
        free(current);
        current = next;
    }
}
