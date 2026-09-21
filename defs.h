#ifndef ACDC_DEFS_H
#define ACDC_DEFS_H
#include <stdio.h>
typedef enum { TOK_EOF, TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_INT } TokenKind;
typedef struct { TokenKind kind; int int_value; } Token;
typedef enum { AST_ADD, AST_SUBTRACT, AST_MULTIPLY, AST_DIVIDE, AST_INT } ASTKind;
typedef struct ASTNode { ASTKind op; struct ASTNode *left; struct ASTNode *right; int int_value; } ASTNode;
#endif
