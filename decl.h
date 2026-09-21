#ifndef ACDC_DECL_H
#define ACDC_DECL_H
#include "defs.h"
int scan_token(Token *token);
ASTNode *make_ast_node(ASTKind op, ASTNode *left, ASTNode *right, int int_value);
ASTNode *make_ast_leaf(ASTKind op, int int_value);
void free_ast(ASTNode *node);
ASTNode *parse_expression(int previous_precedence);
int interpret_ast(ASTNode *node);
void generate_code(ASTNode *node);
void cg_free_all_registers(void);
void cg_preamble(void);
void cg_postamble(void);
int cg_load(int value);
int cg_add(int left_reg, int right_reg);
int cg_sub(int left_reg, int right_reg);
int cg_mul(int left_reg, int right_reg);
int cg_div(int left_reg, int right_reg);
void cg_print_int(int reg);
#endif
