#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	int fd;
	int pid;
	int tubo[2];

	pid = fork();
	if (pid == 0)
	{
		fd = open("Heredoc", O_RDONLY | O_CREAT, 0644);
		dup2(fd, 0);
		close(fd);
		execve("/usr/bin/nl", (char *[]) {"nl", NULL}, 0);
	}
	waitpid(pid, NULL, 0);
	return (0);
}