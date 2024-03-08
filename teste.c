#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pid_t pid;

    pipe(fd); // Cria uma tubulação

    pid = fork(); // Cria um processo filho

    if (pid == 0) {
		printf("entrou filho\n");
        // Processo filho
        close(fd[1]); // Fecha a extremidade de escrita do pipe
        dup2(fd[0], STDIN_FILENO); // Redireciona a entrada padrão para a extremidade de leitura do pipe
        close(fd[0]); // Fecha a extremidade de leitura do pipe

        // Define argumentos para o programa que será executado (por exemplo, "wc -l")
        char *args[] = {"wc", "-l", NULL};
        // Define o ambiente de execução (vazio para herdar do processo pai)
        char *envp[] = {NULL};

        // Executa o programa com execve()
        execve("/usr/bin/wc", args, envp);
        // Se execve retornar, algo deu errado
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
		printf("entrou pai\n");
        // Processo pai
        close(fd[0]); // Fecha a extremidade de leitura do pipe
        dup2(fd[1], STDOUT_FILENO); // Redireciona a saída padrão para a extremidade de escrita do pipe
        close(fd[1]); // Fecha a extremidade de escrita do pipe

        // Define argumentos para o programa cuja saída será redirecionada para o pipe (por exemplo, "ls")
        char *args[] = {"ls", NULL};
        // Define o ambiente de execução (vazio para herdar do processo pai)
        char *envp[] = {NULL};

        // Executa o programa com execve()
        execve("/bin/ls", args, envp);
        // Se execve retornar, algo deu errado
        perror("execve");
        exit(EXIT_FAILURE);
    }

    return 0;
}
