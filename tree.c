#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "decl.h"

// Create a generic AST node.
ASTNode *make_ast_node(
    ASTKind op,
    ASTNode *left,
    ASTNode *right,
    int int_value)
{
    ASTNode *node = malloc(sizeof(*node));

    if (node == NULL) {
        fprintf(stderr, "out of memory while creating AST node\n");
        exit(EXIT_FAILURE);
    }

    node->op = op;
    node->left = left;
    node->right = right;
    node->int_value = int_value;

    return node;
}

// Create an AST leaf node.
ASTNode *make_ast_leaf(ASTKind op, int int_value)
{
    return make_ast_node(op, NULL, NULL, int_value);
}

// Recursively release an AST.
void free_ast(ASTNode *node)
{
    if (node == NULL) {
        return;
    }

    free_ast(node->left);
    free_ast(node->right);
    free(node);
}
