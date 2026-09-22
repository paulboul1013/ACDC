#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

static ASTKind token_to_ast(TokenKind kind)
{
    switch (kind) {
    case TOK_PLUS:  return AST_ADD;
    case TOK_MINUS: return AST_SUBTRACT;
    case TOK_STAR:  return AST_MULTIPLY;
    case TOK_SLASH: return AST_DIVIDE;
    default:
        fprintf(stderr,
                "syntax error on line %d: expected arithmetic operator\n",
                source_line);
        exit(EXIT_FAILURE);
    }
}

static int token_precedence(TokenKind kind)
{
    switch (kind) {
    case TOK_PLUS:
    case TOK_MINUS:
        return 10;
    case TOK_STAR:
    case TOK_SLASH:
        return 20;
    default:
        fprintf(stderr,
                "syntax error on line %d: invalid arithmetic operator\n",
                source_line);
        exit(EXIT_FAILURE);
    }
}

static ASTNode *primary(void)
{
    ASTNode *node;

    if (current_token.kind != TOK_INT) {
        fprintf(stderr,
                "syntax error on line %d: expected integer\n",
                source_line);
        exit(EXIT_FAILURE);
    }

    node = make_ast_leaf(AST_INT, current_token.int_value);
    scan_token(&current_token);
    return node;
}

ASTNode *parse_expression(int previous_precedence)
{
    ASTNode *left;
    ASTNode *right;
    TokenKind operator_token;
    int precedence;

    left = primary();

    operator_token = current_token.kind;
    if (operator_token == TOK_SEMI || operator_token == TOK_EOF) {
        return left;
    }

    precedence = token_precedence(operator_token);

    while (precedence > previous_precedence) {
        scan_token(&current_token);

        right = parse_expression(precedence);

        left = make_ast_node(
            token_to_ast(operator_token),
            left,
            right,
            0
        );

        operator_token = current_token.kind;

        if (operator_token == TOK_SEMI || operator_token == TOK_EOF) {
            return left;
        }

        precedence = token_precedence(operator_token);
    }

    return left;
}
