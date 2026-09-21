#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "decl.h"

static int generate_ast(ASTNode *node) {
    int left_reg, right_reg;
    if (node->op==AST_INT) return cg_load(node->int_value);
    left_reg=generate_ast(node->left);
    right_reg=generate_ast(node->right);
    switch(node->op) {
    case AST_ADD: return cg_add(left_reg,right_reg);
    case AST_SUBTRACT: return cg_sub(left_reg,right_reg);
    case AST_MULTIPLY: return cg_mul(left_reg,right_reg);
    case AST_DIVIDE: return cg_div(left_reg,right_reg);
    case AST_INT: return cg_load(node->int_value);
    }
    fprintf(stderr,"codegen error: unknown AST operation\n"); exit(EXIT_FAILURE);
}

void generate_code(ASTNode *node) {
    cg_preamble();
    int result_reg=generate_ast(node);
    cg_print_int(result_reg);
    cg_postamble();
}
