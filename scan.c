#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

// Return the next character from the input stream.
// If a character was previously put back, return that first.
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

// Save one character so that the next next_char() call returns it.
static void putback_char(int c)
{
    pushed_char = c;
}

// Skip whitespace and return the first non-whitespace character.
static int skip_whitespace(void)
{
    int c = next_char();

    while (c != EOF && isspace((unsigned char)c)) {
        c = next_char();
    }

    return c;
}

// Scan a decimal integer literal.
// first_char is already known to be a digit.
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

// Scan the next token.
// Returns 1 for a normal token and 0 when EOF is reached.
// Even on EOF, token->kind is set to TOK_EOF so the parser
// can explicitly detect the end of the expression.
int scan_token(Token *token)
{
    int c = skip_whitespace();

    if (c == EOF) {
        token->kind = TOK_EOF;
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

    fprintf(
        stderr,
        "scanner error: unexpected character '%c' at line %d\n",
        c,
        source_line
    );

    exit(EXIT_FAILURE);
}
