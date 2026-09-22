#ifndef ACDC_DATA_H
#define ACDC_DATA_H

#include <stdio.h>
#include "defs.h"

extern FILE *source_file;
extern FILE *output_file;
extern int source_line;
extern int pushed_char;
extern Token current_token;
extern char scanner_text[TEXT_LENGTH + 1];

#endif
