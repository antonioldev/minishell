/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:48:27 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:48:27 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_args_array(t_token_list *current)
{
	int	i;

	i = 0;
	if (current->args != NULL)
	{
		while (current->args[i] != NULL)
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		current->args = NULL;
	}
	unlink(".here_doc");
}

void	free_and_set_null(char *str)
{
	free (str);
	str = NULL;
}

void	free_node_and_set_null(t_token_list ***segments)
{
	free(*segments);
	*segments = NULL;
}

void	free_allocation_malloc(t_token_list **lst, char *str,
	t_token_list ***segments)
{
	t_token_list	*current;
	t_token_list	*temp;

	current = *lst;
	if (*lst != NULL)
	{
		while (current != NULL)
		{
			if (current->token == WORD || current->token == SQUOTE
				|| current->token == DQUOTE)
				free_and_set_null (current->value);
			if (current->path != NULL)
				free_and_set_null (current->path);
			free_redirection(&current->infile, &current->outfile);
			free_args_array(current);
			temp = current->next;
			free(current);
			current = temp;
		}
	}
	*lst = NULL;
	if (str != NULL)
		free_and_set_null (str);
	if (*segments != NULL)
		free_node_and_set_null(segments);
}

void	free_allocation_malloc_vars(t_var_list *env_var)
{
	t_var_list	*current;
	t_var_list	*temp;

	current = env_var;
	while (current != NULL)
	{
		if (current->value != NULL)
			free(current->value);
		if (current->key != NULL)
			free(current->key);
		temp = current->next;
		free(current);
		current = temp;
	}
}
