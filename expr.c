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


// Return the precedence of an operator.
//
// Higher number = higher precedence.
//
// + -  -> 10
// * /  -> 20
static int token_precedence(TokenKind kind)
{
    switch (kind) {
    case TOK_PLUS:
    case TOK_MINUS:
        return 10;

    case TOK_STAR:
    case TOK_SLASH:
        return 20;

    case TOK_EOF:
        return 0;

    default:
        fprintf(
            stderr,
            "syntax error on line %d: invalid operator\n",
            source_line
        );

        exit(EXIT_FAILURE);
    }
}


// Parse an integer literal.
//
// Current grammar:
//
// primary:
//     TOK_INT
//
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

    // Build an AST leaf for the integer.
    node = make_ast_leaf(
        AST_INT,
        current_token.int_value
    );

    // Consume the integer token.
    scan_token(&current_token);

    return node;
}


// Parse a binary expression while respecting operator precedence.
//
// previous_precedence:
//     precedence of the operator from the previous recursion level.
//
// Initial call:
//     parse_expression(0)
//
// Example:
//
//     2 + 3 * 5
//
//     + precedence = 10
//     * precedence = 20
//
// Because 20 > 10, 3 * 5 is grouped first.
//
ASTNode *parse_expression(int previous_precedence)
{
    ASTNode *left;
    ASTNode *right;

    TokenKind operator_token;
    int precedence;

    // Parse the left operand.
    left = primary();

    // Remember the operator after the left operand.
    operator_token = current_token.kind;

    // No operator: expression is finished.
    if (operator_token == TOK_EOF) {
        return left;
    }

    precedence = token_precedence(operator_token);

    /*
     * Keep consuming operators while their precedence is
     * higher than the operator from the previous recursion level.
     */
    while (precedence > previous_precedence) {

        // Consume the operator.
        scan_token(&current_token);

        /*
         * Parse the right-hand side.
         *
         * Pass this operator's precedence downward so that
         * higher-precedence operators bind more tightly.
         */
        right = parse_expression(precedence);

        // Join left and right into a new AST.
        left = make_ast_node(
            token_to_ast(operator_token),
            left,
            right,
            0
        );

        // Look at the next operator.
        operator_token = current_token.kind;

        if (operator_token == TOK_EOF) {
            return left;
        }

        precedence = token_precedence(operator_token);
    }

    return left;
}