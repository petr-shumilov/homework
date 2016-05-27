#ifndef ASM_H
#define ASM_H

//declaration and subfunctions 
typedef enum
{
    LD,
    ST,
    LDC,
    ADD,
    SUB,
    CMP,
    JMP,
    BR,
    RET
} instruct_t;

typedef struct command_t
{
    instruct_t instruct;
    char* arg;
} command_t;

typedef enum
{
    ALLOCATE,
    UNKNOWN_COMMAND,
    FILE_OPEN
} error_t;


int _construct_command_t(command_t* command, char* instruct, char* arg)
{
    if (!strcmp(instruct, "ld"))
        command->instruct = LD;
    else if (!strcmp(instruct, "st"))
        command->instruct = ST;
    else if (!strcmp(instruct, "ldc"))
        command->instruct = LDC;
    else if (!strcmp(instruct, "add"))
        command->instruct = ADD;
    else if (!strcmp(instruct, "sub"))
        command->instruct = SUB;
    else if (!strcmp(instruct, "cmp"))
        command->instruct = CMP;
    else if (!strcmp(instruct, "jmp"))
        command->instruct = JMP;
    else if (!strcmp(instruct, "br"))
        command->instruct = BR;
    else if (!strcmp(instruct, "ret"))
        command->instruct = RET;
    else
        return 0;
    command->arg = arg;
    return 1;
}



void error_print(error_t error)
{
    switch (error)
    {
        case ALLOCATE:
            printf("ERROR: couldn't allocate memory\n");
            break;
        case UNKNOWN_COMMAND:
            printf("ERROR: unknown command. skipped\n");
            break;
        case FILE_OPEN:
            printf("ERROR: couldn't open the file\n");
        default:
            printf("Unknown error");
            break;
    }
}

char *trim(char *str)
{
    char *end;
    while(isspace(*str))
        str++;
    if(*str == 0) 
        return str;
    end = str + strlen(str) - 1;
    while(end > str && isspace(*end))
        end--;
    *(end + 1) = 0;
    return str;
}

int strpos(char *needle, char *haystack)
{
   char *p = strstr(haystack, needle);
   if (p != NULL)
      return p - haystack;
   return -1;   // Not found = -1.
}

char* substr(char *string, int position, int length) 
{
    char *buf = malloc(sizeof(char) * MAX_INSTRUCT_LEN);
    if (buf == NULL)
    {
        error_print(ALLOCATE);
        exit(1);
    }
    strncpy(buf, (string + position), length);
    return buf;
}

void reverse(char s[])
{
    int i, j;
    char c;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) 
        n = -n;          
    i = 0;
    do
    {     
        s[i++] = n % 10 + '0';  
    } while ((n /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


#endif //ASM_H