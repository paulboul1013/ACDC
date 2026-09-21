#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

// Convert a scanner token into an AST binary operation.
static ASTKind token_to_ast(TokenKind kind)
{
    switch (kind) {
    case TOK_PLUS:
        return AST_ADD;

    case TOK_MINUS:
        return AST_SUBTRACT;

    case TOK_STAR:
        return AST_MULTIPLY;

    case TOK_SLASH:
        return AST_DIVIDE;

    default:
        fprintf(
            stderr,
            "syntax error on line %d: expected operator\n",
            source_line
        );
        exit(EXIT_FAILURE);
    }
}

// Parse the most basic expression currently supported:
// one integer literal.
//
// This function also consumes the integer token and leaves
// current_token pointing at the next token.
static ASTNode *primary(void)
{
    ASTNode *node;

    if (current_token.kind != TOK_INT) {
        fprintf(
            stderr,
            "syntax error on line %d: expected integer\n",
            source_line
        );
        exit(EXIT_FAILURE);
    }

    node = make_ast_leaf(
        AST_INT,
        current_token.int_value
    );

    // Consume the integer and fetch one-token lookahead.
    scan_token(&current_token);

    return node;
}

// Naive recursive binary-expression parser.
//
// Important: Part 2 intentionally gives every operator the same
// precedence and makes expressions right-associative.
// Part 3 will fix operator precedence.
ASTNode *parse_expression(void)
{
    ASTNode *left;
    ASTNode *right;
    ASTKind op;

    // expression begins with an integer in the current grammar.
    left = primary();

    // Base case of the recursion.
    if (current_token.kind == TOK_EOF) {
        return left;
    }

    // Current token must be a binary arithmetic operator.
    op = token_to_ast(current_token.kind);

    // Consume the operator.
    scan_token(&current_token);

    // Recursively parse everything on the right.
    right = parse_expression();

    return make_ast_node(
        op,
        left,
        right,
        0
    );
}
