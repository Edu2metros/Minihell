#include "../include/minishell.h"

void minishell(const char *str, t_minishell *mini, char **envp)
{
	char **tokens;
	tokens = ft_split(str, ' ');
	if(validate_tokens(tokens, envp, mini) == 0)
		return ;
	
}

int	main(int argc, char **argv, char **envp)
{
	const char	*str;
	int			key;
	t_minishell	mini;

	key = 0;
	str = NULL;
	get_path(envp, &mini);
	while (1)
	{
		str = "Minishell $> ";
		str = readline(str);
		minishell(str, &mini, envp);
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