#include "defs.h"
#include "data.h"
#include "decl.h"

/*
 * Grammar:
 *
 * statements:
 *       statement
 *     | statement statements
 *     ;
 *
 * statement:
 *       'print' expression ';'
 *     ;
 */
void parse_statements(void)
{
    while (current_token.kind != TOK_EOF) {
        ASTNode *tree;
        int result_reg;

        match_token(TOK_PRINT, "'print'");

        tree = parse_expression(0);

        result_reg = gen_ast(tree);
        gen_print_int(result_reg);
        gen_free_registers();

        free_ast(tree);

        match_semicolon();
    }
}
