#include <codegen.h>
#include <tacgen.h>

namespace backend {
    void create_printf_code() {

        CodeGen::add_to_asm(".globl printf", "Make print_f function globally visible", false);
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("printf:", "Start of print_f function", false);
        CodeGen::add_to_asm("move $t1, $a0", "Copy string address to temp register");
        CodeGen::add_to_asm("li $t2, '%'", "Load comparison character");
        CodeGen::add_to_asm("li $s0, 'c'", "Character format specifier");
        CodeGen::add_to_asm("li $s1, 'd'", "Double format specifier");
        CodeGen::add_to_asm("li $s3, 'i'", "Integer format specifier");
        CodeGen::add_to_asm("li $s4, 'f'", "Float format specifier");
        CodeGen::add_to_asm("li $s5, 1", "Initialize count value");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("char_loop:", "Main character processing loop", false);
        CodeGen::add_to_asm("lb $t0, ($t1)", "Load current character");
        CodeGen::add_to_asm("beqz $t0, end_print", "Exit on null terminator");
        CodeGen::add_to_asm("beq $t0, $t2, check_specifier", "Check if character is a format specifier");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("# Print current character", "", false);
        CodeGen::add_to_asm("move $a0, $t0", "Set character for syscall");
        CodeGen::add_to_asm("li $v0, 11", "Syscall 11: print_char");
        CodeGen::add_to_asm("syscall", "Call system function");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("addi $t1, $t1, 1", "Move to next character");
        CodeGen::add_to_asm("j char_loop", "Continue loop");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("check_specifier:", "Process format specifier", false);
        CodeGen::add_to_asm("addi $t1, $t1, 1", "Move to next character");
        CodeGen::add_to_asm("lb $t0, ($t1)", "Load next character");
        CodeGen::add_to_asm("beqz $t0, end_print_percent", "Exit on null terminator");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("# Check for format specifiers", "", false);
        CodeGen::add_to_asm("beq $t0, $s0, print_char", "Check for 'c' specifier");
        CodeGen::add_to_asm("beq $t0, $s1, print_double", "Check for 'd' specifier");
        CodeGen::add_to_asm("beq $t0, $s3, print_int", "Check for 'i' specifier");
        CodeGen::add_to_asm("beq $t0, $s4, print_float", "Check for 'f' specifier");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("j char_loop", "Continue printing characters");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("end_print_percent:", "Handle case where % is last character", false);
        CodeGen::add_to_asm("move $a0, $t2", "Print the '%' character");
        CodeGen::add_to_asm("li $v0, 11", "Syscall 11: print_char");
        CodeGen::add_to_asm("syscall", "Call system function");
        CodeGen::add_to_asm("end_print:", "End of print_f function", false);
        CodeGen::add_to_asm("move $v0, $s5", "Move character count to $v0");
        CodeGen::add_to_asm("jr $ra", "Return to caller");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("print_char:", "Handle character format specifier", false);
        CodeGen::add_to_asm("lb $a0, ($sp)", "Load character from stack");
        CodeGen::add_to_asm("li $v0, 11", "Syscall 11: print_char");
        CodeGen::add_to_asm("syscall", "Call system function");
        CodeGen::add_to_asm("addi $sp, $sp, 4", "Adjust stack pointer");
        CodeGen::add_to_asm("addi $s5, $s5, 1", "Increment character count");
        CodeGen::add_to_asm("addi $t1, $t1, 1", "Move to next character");
        CodeGen::add_to_asm("j char_loop", "Continue printing characters");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("print_int:", "Handle integer format specifier", false);
        CodeGen::add_to_asm("lw $a0, ($sp)", "Load integer from stack");
        CodeGen::add_to_asm("li $v0, 1", "Syscall 1: print_int");
        CodeGen::add_to_asm("syscall", "Call system function");
        CodeGen::add_to_asm("addi $sp, $sp, 4", "Adjust stack pointer");
        CodeGen::add_to_asm("addi $s5, $s5, 1", "Increment integer count");
        CodeGen::add_to_asm("addi $t1, $t1, 1", "Move to next character");
        CodeGen::add_to_asm("j char_loop", "Continue printing characters");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("print_float:", "Handle float format specifier", false);
        CodeGen::add_to_asm("lwc1 $f12, ($sp)", "Load float from stack");
        CodeGen::add_to_asm("li $v0, 2", "Syscall 2: print_float");
        CodeGen::add_to_asm("syscall", "Call system function");
        CodeGen::add_to_asm("addi $sp, $sp, 4", "Adjust stack pointer");
        CodeGen::add_to_asm("addi $s5, $s5, 1", "Increment float count");
        CodeGen::add_to_asm("addi $t1, $t1, 1", "Move to next character");
        CodeGen::add_to_asm("j char_loop", "Continue printing characters");
        CodeGen::add_to_asm("", "");
        CodeGen::add_to_asm("print_double:", "Handle double format specifier", false);
        CodeGen::add_to_asm("ldc1 $f12, ($sp)", "Load double from stack");
        CodeGen::add_to_asm("li $v0, 3", "Syscall 3: print_double");
        CodeGen::add_to_asm("syscall", "Call system function");
        CodeGen::add_to_asm("addi $sp, $sp, 8", "Adjust stack pointer for double");
        CodeGen::add_to_asm("addi $s5, $s5, 1", "Increment double count");
        CodeGen::add_to_asm("addi $t1, $t1, 1", "Move to next character");
        CodeGen::add_to_asm("j char_loop", "Continue printing characters");
        CodeGen::add_to_asm("", "");
    }
}