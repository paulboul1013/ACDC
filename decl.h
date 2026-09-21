#ifndef ACDC_DECL_H
#define ACDC_DECL_H

#include "defs.h"


// Scanner
int scan_token(Token *token);


// AST construction
ASTNode *make_ast_node(
    ASTKind op,
    ASTNode *left,
    ASTNode *right,
    int int_value
);

ASTNode *make_ast_leaf(
    ASTKind op,
    int int_value
);


// Parser
ASTNode *parse_expression(int previous_precedence);


// Interpreter
int interpret_ast(ASTNode *node);


// AST cleanup
void free_ast(ASTNode *node);


#endif