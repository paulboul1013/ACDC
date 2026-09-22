# ACDC Part 5 — Statements

Part 5 extends ACDC from compiling one expression to compiling a sequence
of `print` statements.

Grammar:

    statements:
          statement
        | statement statements
        ;

    statement:
          'print' expression ';'
        ;

Build:

    make

Compile:

    ./acdc input01

Assemble/link generated code:

    gcc -o out out.s

Run:

    ./out

Expected output for input01:

    36
    10
    25
