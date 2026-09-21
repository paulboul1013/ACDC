#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

FILE *source_file = NULL;
int source_line = 1;
int pushed_char = EOF;

static const char *token_name(TokenKind kind)
{
    switch (kind) {
    case TOK_PLUS:
        return "PLUS";
    case TOK_MINUS:
        return "MINUS";
    case TOK_STAR:
        return "STAR";
    case TOK_SLASH:
        return "SLASH";
    case TOK_INT:
        return "INT";
    }

    return "UNKNOWN";
}

static void scan_file(void)
{
    Token token;

    while (scan_token(&token)) {
        printf("Token %-6s", token_name(token.kind));

        if (token.kind == TOK_INT) {
            printf(" value=%d", token.int_value);
        }

        putchar('\n');
    }
}

static void usage(const char *program)
{
    fprintf(stderr, "usage: %s <source-file>\n", program);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    source_file = fopen(argv[1], "r");

    if (source_file == NULL) {
        fprintf(stderr,
                "cannot open '%s': %s\n",
                argv[1],
                strerror(errno));
        return EXIT_FAILURE;
    }

    scan_file();
    fclose(source_file);

    return EXIT_SUCCESS;
}
