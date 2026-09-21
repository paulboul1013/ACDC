#ifndef ACDC_DATA_H
#define ACDC_DATA_H

#include <stdio.h>
#include "defs.h"

// Scanner state.
extern FILE *source_file;
extern int source_line;
extern int pushed_char;

// One-token lookahead used by the parser.
extern Token current_token;

#endif
