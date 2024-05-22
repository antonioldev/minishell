/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_unwanted_nodes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:01:10 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/17 16:07:07 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Remove nodes from token list when not needed anymore*/
void	token_remove_unwanted_nodes(t_token_list **head)
{
	t_token_list	*current;
	t_token_list	*next_node;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->to_remove == true)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->value != NULL)
				free(current->value);
			free(current);
		}
		current = next_node;
	}
}

/*Remove nodes from variables list when find a duplicate*/
void	var_remove_unwanted_nodes(t_var_list **head)
{
	t_var_list	*current;
	t_var_list	*next_node;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->to_remove == true)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->value != NULL)
				free(current->value);
			if (current->key != NULL)
				free(current->key);
			free(current);
		}
		current = next_node;
	}
}

/*Remove nodes from token list when find a duplicate*/
void	remove_pipes_and_args(t_token_list **head)
{
	t_token_list	*current;

	current = *head;
	while (current != NULL)
	{
		if (current->token == PIPE || current->type == ARG)
			current->to_remove = true;
		current = current->next;
	}
}

/*Close all pipes*/
void	close_all_pipes(t_state *s)
{
	int	i;

	i = 0;
	while (i < s->number_commands)
	{
		close(s->pipes[i][0]);
		close(s->pipes[i][1]);
		i++;
	}
}
