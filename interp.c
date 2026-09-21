#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "decl.h"

// Recursively evaluate an AST.
//
// Part 2 uses this as an interpreter so that we can observe whether
// the parser built the intended tree.
int interpret_ast(ASTNode *node)
{
    int left;
    int right;

    if (node->op == AST_INT) {
        printf("int %d\n", node->int_value);
        return node->int_value;
    }

    left = interpret_ast(node->left);
    right = interpret_ast(node->right);

    switch (node->op) {
    case AST_ADD:
        printf("%d + %d\n", left, right);
        return left + right;

    case AST_SUBTRACT:
        printf("%d - %d\n", left, right);
        return left - right;

    case AST_MULTIPLY:
        printf("%d * %d\n", left, right);
        return left * right;

    case AST_DIVIDE:
        printf("%d / %d\n", left, right);
        return left / right;

    case AST_INT:
        // Already handled above.
        return node->int_value;
    }

    fprintf(stderr, "interpreter error: unknown AST operation\n");
    exit(EXIT_FAILURE);
}
