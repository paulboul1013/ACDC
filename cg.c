#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "decl.h"

static int register_free[4];
static const char *reg_names[4] = { "%r8", "%r9", "%r10", "%r11" };

void cg_free_all_registers(void) { for(int i=0;i<4;i++) register_free[i]=1; }

static int allocate_register(void) {
    for(int i=0;i<4;i++) if(register_free[i]) { register_free[i]=0; return i; }
    fprintf(stderr,"codegen error: out of registers\n"); exit(EXIT_FAILURE);
}

static void free_register(int reg) {
    if (reg<0 || reg>=4 || register_free[reg]) { fprintf(stderr,"codegen error: invalid register free\n"); exit(EXIT_FAILURE); }
    register_free[reg]=1;
}

void cg_preamble(void) {
    cg_free_all_registers();
    fputs(
        "\t.section .rodata\n"
        ".LC0:\n"
        "\t.string \"%ld\\n\"\n"
        "\n"
        "\t.text\n"
        "printint:\n"
        "\tpushq %rbp\n"
        "\tmovq %rsp, %rbp\n"
        "\tmovq %rdi, %rsi\n"
        "\tleaq .LC0(%rip), %rdi\n"
        "\txorl %eax, %eax\n"
        "\tcall printf@PLT\n"
        "\tpopq %rbp\n"
        "\tret\n"
        "\n"
        "\t.globl main\n"
        "\t.type main, @function\n"
        "main:\n"
        "\tpushq %rbp\n"
        "\tmovq %rsp, %rbp\n", output_file);
}

void cg_postamble(void) {
    fputs(
        "\tmovl $0, %eax\n"
        "\tpopq %rbp\n"
        "\tret\n"
        "\t.section .note.GNU-stack,\"\",@progbits\n", output_file);
}

int cg_load(int value) {
    int reg=allocate_register();
    fprintf(output_file,"\tmovq $%d, %s\n",value,reg_names[reg]);
    return reg;
}

int cg_add(int left_reg,int right_reg) {
    fprintf(output_file,"\taddq %s, %s\n",reg_names[left_reg],reg_names[right_reg]);
    free_register(left_reg); return right_reg;
}
int cg_mul(int left_reg,int right_reg) {
    fprintf(output_file,"\timulq %s, %s\n",reg_names[left_reg],reg_names[right_reg]);
    free_register(left_reg); return right_reg;
}
int cg_sub(int left_reg,int right_reg) {
    fprintf(output_file,"\tsubq %s, %s\n",reg_names[right_reg],reg_names[left_reg]);
    free_register(right_reg); return left_reg;
}
int cg_div(int left_reg,int right_reg) {
    fprintf(output_file,"\tmovq %s, %%rax\n",reg_names[left_reg]);
    fprintf(output_file,"\tcqo\n");
    fprintf(output_file,"\tidivq %s\n",reg_names[right_reg]);
    fprintf(output_file,"\tmovq %%rax, %s\n",reg_names[left_reg]);
    free_register(right_reg); return left_reg;
}
void cg_print_int(int reg) {
    fprintf(output_file,"\tmovq %s, %%rdi\n",reg_names[reg]);
    fprintf(output_file,"\tcall printint\n");
    free_register(reg);
}
