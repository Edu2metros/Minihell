#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	handle_error(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
		exit(printf("Aspa aberta fecha\n"));
}

int	main(void)
{
	const char *exemplo1 = "Esta é uma 'string de exemplo.";
	const char *exemplo2 = "Outro exemplo com \"aspas duplas\".";

	check_quote(exemplo1);
	check_quote(exemplo2);

	return (0);
}