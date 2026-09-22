#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "data.h"
#include "decl.h"

FILE *source_file = NULL;
FILE *output_file = NULL;

int source_line = 1;
int pushed_char = EOF;

Token current_token;
char scanner_text[TEXT_LENGTH + 1];

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

    output_file = fopen("out.s", "w");
    if (output_file == NULL) {
        fprintf(stderr,
                "cannot create 'out.s': %s\n",
                strerror(errno));
        fclose(source_file);
        return EXIT_FAILURE;
    }

    scan_token(&current_token);

    gen_preamble();
    parse_statements();
    gen_postamble();

    fclose(output_file);
    fclose(source_file);

    printf("assembly: out.s\n");

    return EXIT_SUCCESS;
}
