/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jaqribei <jaqribei@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:32:28 by jaqribei          #+#    #+#             */
/*   Updated: 2024/02/14 00:44:29 by  jaqribei        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	new_tree_node(t_minishell *mini)
{
	t_token	*token;
	t_cmd	*tree;

	token = mini->token;
	tree = malloc(sizeof(t_cmd));
	if (!tree)
		exit(0); //add error message
	tree->type = token->type;
	tree->name = ft_strdup(token->content);
	tree->left = NULL;
	tree->right = NULL;
	mini->tree = tree;
}

/*function to create (add content) the left node of the tree*/

t_tree	add_left_node(t_minishell *mini)
{
	t_tree	*tree;
	t_token	*token;
	
	tree->left = create_tree(mini);
	
}

/*function to create (add content) the left node of the tree*/

t_tree	add_right_left(t_minishell *mini)
{
	t_tree	*tree;
	t_token	*token;
	
	tree->right = create_tree(mini);
}

/*

walk through the list of tokens to create the tree (?)

or create a new list before the tree (?)

*/
void	parser_tree(t_minishell *mini)
{
	t_token	*token;
	t_tree	*tree;

	while (token != NULL)
	{
		if (token->type == 3)
			tree->left == token->previous; //(add_node_left)
			tree->right = token->next; // (add_right_node)
		token = token->next;
	}
}

/*	if (token == heredoc)
		heredoc
	if (token = pipe)
		pipe
*/

void	cmd_list(t_minishell *mini, char *input)
{
	
}

void	add_cmd_node(t_minishell *mini)
{
	
}