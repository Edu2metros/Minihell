#include "../include/minishell.h"

void exec(t_minishell *mini, t_cmd *cmd)
{
    int fd[2];
    int fd_in = STDIN_FILENO;
    pid_t pid;

    while(cmd)
    {
        pipe(fd);
        pid = fork();
        if(pid == 0)
        {
            if(fd_in != STDIN_FILENO)
            {
                dup2(fd_in, STDIN_FILENO);
                close(fd_in);
            }
            if(cmd->next != NULL)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
            }
            exec_command(cmd, mini);
            exit(0);
        }
        else
        {
            wait(NULL);
            if(fd_in != STDIN_FILENO)
                close(fd_in);
            close(fd[1]);
            fd_in = fd[0];
            cmd = cmd->next;
        }
    }
}
