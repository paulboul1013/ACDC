#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

void match_token(TokenKind expected, const char *description)
{
    if (current_token.kind != expected) {
        fprintf(stderr,
                "syntax error on line %d: expected %s\n",
                source_line,
                description);
        exit(EXIT_FAILURE);
    }

    scan_token(&current_token);
}

void match_semicolon(void)
{
    match_token(TOK_SEMI, "';'");
}
