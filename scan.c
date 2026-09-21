#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

static int next_char(void)
{
    int c;

    if (pushed_char != EOF) {
        c = pushed_char;
        pushed_char = EOF;
        return c;
    }

    c = fgetc(source_file);

    if (c == '\n') {
        source_line++;
    }

    return c;
}

static void putback_char(int c)
{
    pushed_char = c;
}

static int skip_whitespace(void)
{
    int c = next_char();

    while (c != EOF && isspace((unsigned char)c)) {
        c = next_char();
    }

    return c;
}

static int scan_integer(int first_char)
{
    int value = 0;
    int c = first_char;

    while (c != EOF && isdigit((unsigned char)c)) {
        value = value * 10 + (c - '0');
        c = next_char();
    }

    if (c != EOF) {
        putback_char(c);
    }

    return value;
}

int scan_token(Token *token)
{
    int c = skip_whitespace();

    if (c == EOF) {
        return 0;
    }

    switch (c) {
    case '+':
        token->kind = TOK_PLUS;
        return 1;
    case '-':
        token->kind = TOK_MINUS;
        return 1;
    case '*':
        token->kind = TOK_STAR;
        return 1;
    case '/':
        token->kind = TOK_SLASH;
        return 1;
    default:
        break;
    }

    if (isdigit((unsigned char)c)) {
        token->kind = TOK_INT;
        token->int_value = scan_integer(c);
        return 1;
    }

    fprintf(stderr,
            "scanner error: unexpected character '%c' at line %d\n",
            c,
            source_line);
    exit(EXIT_FAILURE);
}
