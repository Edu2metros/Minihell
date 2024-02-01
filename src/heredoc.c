#include "../include/minishell.h"

int main(int argc, char **argv) {
    char *prompt;
    int tube[2];
    if(argc != 2)
        return(EXIT_FAILURE);
    pipe(tube);
    while (1) 
    {
        prompt = readline("$> ");
        if (ft_strcmp(prompt, argv[1]) == 0)
        {
            free(prompt);
            break;
        }
        ft_putstr_fd(prompt, tube[1]);
        ft_putstr_fd("\n", tube[1]);
        free(prompt);
    }

    close(tube[1]);
    return 0;
}
