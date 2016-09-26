#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


typedef struct command_t
{
    const char *file;
    char **argv;
    
} command_t;

typedef struct redirectable_t 
{
    command_t command;
    
    int input_exist;
    int output_exist;

    char *input_file;
    char *output_file;
    
} redirectable_t;

 
int make_proc(int fd_in, int fd_out, command_t *cmd)
{
    // init process handler
    pid_t pid = fork ();

    // if new proc is child
    if (pid == 0)
    {
        // input 
        if (fd_in != 0)
        {
            // switch 
            dup2(fd_in, 0);
            close(fd_in);
        }
        if (fd_out != 1)
        {
            // now stdout will be begin of the pipe     
            dup2(fd_out, 1);
            close (fd_out);
        }
        return execvp (cmd->argv[0], cmd->argv);
    }
    return pid;
}

int fork_pipes (int n, redirectable_t *cmd)
{
    int i;
    int in, fd [2];

    // the first process should get its input from stdin   
    in = 0;

    for (i = 0; i < n - 1; ++i)
    {
        // create anonymous pipe
        pipe (fd);

        // f[1] is the write end of the pipe, we carry `in` from the prev iteration.  
        make_proc(in, fd[1], &cmd[i].command);

        // no need for the write end of the pipe, the child will write here.  
        close (fd [1]);

        // keep the read end of the pipe
        in = fd [0];
    }


    if (in != 0)
        dup2 (in, 0);
    if (cmd[i].output_exist)
    {
        int out = open(cmd[i].output_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
        dup2(out, 1);
        close(out);
    }
    execvp (cmd[i].command.argv [0], cmd[i].command.argv);

    return 1;
}



int main()
{
    command_t seq;
    seq.file = "seq";
    seq.argv = malloc(4 * sizeof(char **));
    seq.argv[0] = (char *)seq.file;
    seq.argv[1] = "1";
    seq.argv[2] = "10";
    seq.argv[3] = 0;
    
    command_t grep;
    grep.file = "grep";
    grep.argv = malloc(3 * sizeof(char **));
    grep.argv[0] = (char *)grep.file;
    grep.argv[1] = "1";
    grep.argv[2] = 0;
    

    redirectable_t seq1;
    seq1.command = seq;
    seq1.input_exist = 0;
    seq1.output_exist = 0;
    seq1.input_file = "";
    seq1.output_file = "";

    redirectable_t grep1;
    grep1.command = grep;
    grep1.input_exist = 0;
    grep1.output_exist = 1;
    grep1.input_file = "";
    grep1.output_file = "a.out";
    
    
    redirectable_t cmd[] = {seq1, grep1};

    fork_pipes (2, cmd);
    return 0;
}