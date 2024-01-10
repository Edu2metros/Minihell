#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	const char	*str;
	char		**token;
	int			key;
	t_minishell	mini;

	key = 0;
	str = NULL;
	get_path(envp, &mini);
	while (1)
	{
		str = "Minishell $> ";
		str = readline(str);
		token = ft_split(str, ' ');
		key = validate_tokens(token, envp, &mini);
		if (key == 0)
			printf("Command not found.\n");
	}
}

/* mostrar o prompt
ler o comando de usuário
executar (???)


Parser -> interpretar o comando,
	por exemplo eu mando: echo 'Hello World' > output.txt
Built-in -> comandos e funcionalidades já incorporados no sistema,
	--Váriavel de ambiente PATH--

step by step:
main -> ler linha -> tokenizar -> interpretar -> mandar pro PATH
*/