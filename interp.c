#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "decl.h"

int interpret_ast(ASTNode *node) {
    if (node->op==AST_INT) return node->int_value;
    int left=interpret_ast(node->left);
    int right=interpret_ast(node->right);
    switch(node->op) {
    case AST_ADD: return left+right;
    case AST_SUBTRACT: return left-right;
    case AST_MULTIPLY: return left*right;
    case AST_DIVIDE: return left/right;
    case AST_INT: return node->int_value;
    }
    fprintf(stderr,"interpreter error: unknown AST operation\n"); exit(EXIT_FAILURE);
}
