#include "../../include/minishell.h"

void	hash_update_value(t_hash_table *hash, char *key)
{
	char	*equal_pos;
	int		key_length;
	int		i;

	equal_pos = ft_strchr(key, '=');
	if (equal_pos == NULL)
		equal_pos = 0;
	i = 0;
	while (i < hash->size)
	{
		if (hash->item[i])
		{
			key_length = equal_pos - key;
			if (ft_strncmp(hash->item[i]->key, key, key_length) == 0)
			{
				free(hash->item[i]->value);
				if (equal_pos == 0)
					hash->item[i]->value = ft_strdup("");
				else
					hash->item[i]->value = ft_strdup(equal_pos + 1);
				break ;
			}
		}
		i++;
	}
}

int	ft_is_stralnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isall_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_error(char *str, t_hash_table *hash)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
		{
			ft_printf_fd(STDERR_FILENO, "minishell: export: `%s': not a valid \
			identifier\n", str);
			get_control()->return_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	export(t_cmd *cmd, t_hash_table *hash)
{
	char	*equal_pos;
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (ft_array_len(cmd->args) == 1)
		print_export(hash, cmd);
	else
	{
		while (cmd->args[i])
		{
			if (hash_search(hash, cmd->args[i]) != NULL)
				hash_update_value(hash, cmd->args[i]);
			else if (check_error(cmd->args[i], hash) == 1)
			{
				equal_pos = ft_strchr(cmd->args[i], '=');
				if (equal_pos == NULL)
				{
					key = ft_strdup(cmd->args[i]);
					value = ft_strdup("");
				}
				else
				{
					key = ft_substr(cmd->args[i], 0, equal_pos - cmd->args[i]);
					value = ft_strdup(equal_pos + 1);
					if (!value)
						value = ft_strdup("");
				}
				hash_insert(&hash, key, value);
				free(key);
				if (value)
					free(value);
				get_control()->return_status = 0;
			}
			i++;
		}
	}
	if (get_control()->cmd->on_fork == 1)
		exit(get_control()->return_status);
}
