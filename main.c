#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "data.h"
#include "decl.h"


// Definitions for global state declared in data.h.
FILE *source_file = NULL;

int source_line = 1;

int pushed_char = EOF;

Token current_token;


static void usage(const char *program)
{
    fprintf(
        stderr,
        "usage: %s <source-file>\n",
        program
    );
}


int main(int argc, char **argv)
{
    ASTNode *tree;
    int result;

    if (argc != 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    source_file = fopen(argv[1], "r");

    if (source_file == NULL) {
        fprintf(
            stderr,
            "cannot open '%s': %s\n",
            argv[1],
            strerror(errno)
        );

        return EXIT_FAILURE;
    }


    // Get first token.
    scan_token(&current_token);


    // Token stream -> AST.
    //
    // 0 means:
    // start parsing from the lowest precedence level.
    tree = parse_expression(0);


    // AST -> result.
    result = interpret_ast(tree);

    printf("%d\n", result);


    free_ast(tree);

    fclose(source_file);

    return EXIT_SUCCESS;
}