#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "decl.h"

int gen_ast(ASTNode *node)
{
    int left_reg;
    int right_reg;

    if (node->op == AST_INT) {
        return cg_load(node->int_value);
    }

    left_reg = gen_ast(node->left);
    right_reg = gen_ast(node->right);

    switch (node->op) {
    case AST_ADD:
        return cg_add(left_reg, right_reg);
    case AST_SUBTRACT:
        return cg_sub(left_reg, right_reg);
    case AST_MULTIPLY:
        return cg_mul(left_reg, right_reg);
    case AST_DIVIDE:
        return cg_div(left_reg, right_reg);
    case AST_INT:
        return cg_load(node->int_value);
    }

    fprintf(stderr, "codegen error: unknown AST operation\n");
    exit(EXIT_FAILURE);
}

void gen_preamble(void)
{
    cg_preamble();
}

void gen_postamble(void)
{
    cg_postamble();
}

void gen_free_registers(void)
{
    cg_free_all_registers();
}

void gen_print_int(int reg)
{
    cg_print_int(reg);
}
