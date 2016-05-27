#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ASM_SOURCE "first.asm"
#define MAX_ADDRESS 10000000
#define MAX_COMMANDS 1000
#define MAX_INSTRUCT_LEN 40
#define MAX_ARG_LEN 40

#include "asm.h"
#include "stack.h"
#include "hash_table.h"

stack_t *stack;
int32_t *memory;

void do_ld(char* arg);

void do_st(char* arg);

void do_ldc(char* arg);

void do_add();

void do_sub();

void do_cmp();

void debug_mem(int len)
{
    printf("\n--------------------\n");
    int i;
    for (i = 0; i < len; ++i)
        printf("%d ", memory[i]);
    printf("\n--------------------\n");
}

int main()
{
    // init 'local' memory
    memory = malloc(sizeof(int32_t) * MAX_ADDRESS);
    if (memory == NULL)
    {
        error_print(ALLOCATE);
        exit(1);
    }
    
    stack = stack_init();
    if (stack == NULL)
    {
        exit(1);
    }
    
    // init array of execution code
    command_t *code = (command_t*)malloc(sizeof(command_t) * MAX_COMMANDS); 
    if (code == NULL)
    {
        error_print(ALLOCATE);
        exit(1);
    }

    // replacing stl container <map>
    hash_table *labels = create_table(hash_func, HT_SIZE);


    // open asm source file 
    FILE *source_file = fopen(ASM_SOURCE, "r");
    if (source_file == NULL)
    {
        error_print(FILE_OPEN);
        exit(1);
    }

    //read source file
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int line_iter = 0;
    while ((read = getline(&line, &len, source_file)) != -1) 
    {
        line = trim(line);

        char* instruct = malloc(sizeof(char) * MAX_INSTRUCT_LEN);
        if (instruct == NULL)
        {
            error_print(ALLOCATE);
            exit(1);
        }
        char* arg = malloc(sizeof(char) * MAX_ARG_LEN);
        if (arg == NULL)
        {
            error_print(ALLOCATE);
            exit(1);
        }
        
        int label_pos = strpos(":", line);
        int comment_pos = strpos(";", line);
        
        if (comment_pos != -1)
        {
            line = trim(substr(line, 0, comment_pos));
        }
    
        if (label_pos != -1) 
        {
            char* label = trim(substr(line, 0, label_pos));
            ht_set(labels, label, line_iter);
            line = trim(substr(line, label_pos + 1, strlen(line) - label_pos));
        }

        if (strlen(line) == 0)
            continue;
        
        // parse instruction and argument
        sscanf(line, "%s %s", instruct, arg);

        if(!_construct_command_t(&code[line_iter], instruct, trim(arg))) // try construct command 
        {
            error_print(UNKNOWN_COMMAND);
            printf("line: %d\n", line_iter);    
            continue;
        }

        //printf("%s %s\n", instruct, code[line_iter].arg);
        line_iter++;
    }
    //debug_table(labels);
    fclose(source_file);

    int i;
    for (i = 0; i < line_iter; ++i)
    {
        if (code[i].instruct == BR || code[i].instruct == JMP)
            itoa(ht_get(labels, code[i].arg), code[i].arg); // convert label from string to int
    }
    
    //return 0;

    int pntr = 0x0;
    //int k;
    //for (k = 0; k < 30000; ++k)
    while(1)
    {
        switch(code[pntr].instruct)
        {
            case LD:
                do_ld(code[pntr].arg);
                break;
            case ST:
                do_st(code[pntr].arg);
                break;
            case LDC:
                do_ldc(code[pntr].arg);
                break;
            case ADD:
                do_add();
                break;
            case SUB:
                do_sub();
                break;
            case CMP:
                do_cmp();
                break;
            case JMP:
                pntr = atoi(code[pntr].arg);
                continue;
                break;
            case BR:
                if (stack_front(stack))
                {
                    pntr = atoi(code[pntr].arg);
                    continue;
                }
                break;
            case RET:
                printf("===================FINISHED===================\n");
                debug_stack(stack);
                printf("===================FINISHED===================");
                exit(0);
                break;
        }

        int debug = 0;
        if (debug)
        {
            printf("%d)", pntr);
            switch(code[pntr].instruct)
            {
                case LD:
                    printf(" ld ");
                    break;
                case ST:
                    printf(" st ");
                    break;
                case LDC:
                    printf(" ldc ");
                    break;
                case ADD:
                    printf(" add ");
                    break;
                case SUB:
                    printf(" sub ");
                    break;
                case CMP:
                    printf(" cmp ");
                    break;
                case JMP:
                    printf(" jmp ");
                    break;
                case BR:
                    printf(" br ");
                    break;
                case RET:
                    printf(" ret ");
                    break;
            }
            printf("%d\n", atoi(code[pntr].arg));
            debug_stack(stack);
            debug_mem(15);
        }
        pntr++;
    }
    
    return 0;
}

void do_ld(char* arg)
{
    stack_push(stack, memory[atoi(arg)]);
}

void do_st(char* arg)
{
    memory[atoi(arg)] = stack_front(stack);
    stack_pop(stack);
}

void do_ldc(char* arg)
{
    stack_push(stack, atoi(arg));
}

void do_add()
{
    int32_t a = stack_front(stack);
    stack_pop(stack);
    int32_t b = stack_front(stack);
    stack_pop(stack);
    stack_push(stack, a + b);
}

void do_sub()
{
    int32_t a = stack_front(stack);
    stack_pop(stack);
    int32_t b = stack_front(stack);
    stack_pop(stack);
    stack_push(stack, a - b);
}

void do_cmp()
{
    int32_t a = stack_front(stack);
    stack_pop(stack);
    int32_t b = stack_front(stack);
    stack_pop(stack);
    if (a == b)
        stack_push(stack, 0);
    else if (a > b)
        stack_push(stack, 1);
    else
        stack_push(stack, -1);
}
