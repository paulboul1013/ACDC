#ifndef ACDC_DEFS_H
#define ACDC_DEFS_H

#include <stdio.h>

typedef enum {
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_INT
} TokenKind;

typedef struct {
    TokenKind kind;
    int int_value;
} Token;

#endif
