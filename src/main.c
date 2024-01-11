#include "../include/minishell.h"

void	minishell(const char *str, t_minishell *mini, char **envp)
{
	if (validate_input(str, envp, mini) == 0)
		return ;
}
void	print_tokens(t_token *token_list)
{
	t_token	*current_token;

	current_token = token_list;
	while (current_token != NULL)
	{
		printf("Content: %s, Type: %d\n", current_token->content,
			current_token->type);
		current_token = current_token->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;
	const char	*prompt;
	char		**tokens;

	mini = ft_calloc(1, sizeof(t_minishell));
	mini->token = ft_calloc(1, sizeof(t_token));
	mini->token->content = NULL;
	while (1)
	{
		prompt = readline("Minishell $> ");
		minishell(prompt, mini, envp);
		print_tokens(mini->token);
	}
}
