#ifndef TOKEN_H
#define TOKEN_H

// Token types
typedef enum
{
    NUMBER,
    OPERATOR,
    SYMBOL
} TokenType;

typedef struct _token Token;

/***
 * Create a new token of type NUMBER.
 * 
 * 
 * PARAMETERS
 * num              the number
 * 
 * RETURN
 * token            the new token
 *
 */
Token *tokenCreateNumber(double num);

/***
 * Create a new token of type OPERATOR.
 *
 *
 * PARAMETERS
 * op               the operator symbol
 *
 * RETURN
 * token            the new token
 *
 */
Token *tokenCreateOperator(char *op);

/***
 * Create a new token of type SYMBOL.
 *
 *
 * PARAMETERS
 * sym              the symbol
 *
 * RETURN
 * token            the new token
 *
 */
Token *tokenCreateSymbol(char *sym);

/***
 * Get the type of a token.
 *
 *
 * PARAMETERS
 * token            the token
 *
 * RETURN
 * type             the type of the token
 * 
 */
TokenType tokenGetType(Token *token); // à utiliser ? 

/***
 * Get the number of a token of type NUMBER.
 *
 *
 * PARAMETERS
 * token            the token
 *
 * RETURN
 * num              the number of the token
 *
 */
double tokenGetNumber(Token *token); // à utiliser si le token est de type NUMBER

/***
 * Get the operator symbol of a token of type OPERATOR.
 *
 *
 * PARAMETERS
 * token            the token
 *
 * RETURN
 * op               the operator symbol
 *
 */
char *tokenGetOperator(Token *token); // à utiliser si le token est de type OPERATOR

/***
 * Get the symbol of a token of type SYMBOL.
 *
 *
 * PARAMETERS
 * token            the token
 *
 * RETURN
 * sym              the symbol
 *
 */
char *tokenGetSymbol(Token *token); // à utiliser si le token est de type SYMBOL

/***
 * Free all the created tokens.
 *
 */
void tokenFreeAll(void);

#endif
