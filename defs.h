#ifndef ACDC_DEFS_H
#define ACDC_DEFS_H

#include <stdio.h>

// Token types produced by the scanner.
typedef enum {
    TOK_EOF,
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_INT
} TokenKind;

// One lexical token.
typedef struct {
    TokenKind kind;
    int int_value;
} Token;

// AST node types produced by the parser.
typedef enum {
    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,
    AST_INT
} ASTKind;

// Abstract Syntax Tree node.
typedef struct ASTNode {
    ASTKind op;

    struct ASTNode *left;
    struct ASTNode *right;

    // Used by AST_INT nodes.
    int int_value;
} ASTNode;

#endif
