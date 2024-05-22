/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_empty_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:44:30 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/12 16:44:30 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Function to insert a CMD type node after the specified node
void	insert_cmd_node_before(t_token_list *node)
{
	t_token_list	*new_node;

	if (node == NULL)
		return ;
	new_node = token_lstnew(WORD, ft_strdup("true"));
	if (new_node == NULL)
		ft_malloc_error();
	new_node->type = CMD;
	new_node->run = false;
	new_node->prev = node->prev;
	new_node->next = node;
	new_node->is_fake_command = true;
	if (node->prev != NULL)
		node->prev->next = new_node;
	node->prev = new_node;
}

// Function to insert a CMD type node after the specified node
void	insert_cmd_node_after(t_token_list *node)
{
	t_token_list	*new_node;

	if (node == NULL)
		return ;
	new_node = token_lstnew(WORD, ft_strdup("true"));
	if (new_node == NULL)
		ft_malloc_error();
	new_node->type = CMD;
	new_node->run = false;
	new_node->is_fake_command = true;
	node->next = new_node;
	new_node->prev = node;
	new_node->next = NULL;
}

// Function to ensure there is at least one CMD type between each pipe
void	ensure_cmd_between_pipes(t_token_list *token_list)
{
	bool			is_a_cmd;
	t_token_list	*current;

	current = token_list;
	is_a_cmd = false;
	while (current != NULL)
	{
		if (current->type == CMD)
			is_a_cmd = true;
		if (current->token == PIPE)
		{
			if (!is_a_cmd)
				insert_cmd_node_before(current);
			is_a_cmd = false;
		}
		else if (current->next == NULL)
		{
			if (!is_a_cmd)
				insert_cmd_node_after(current);
			is_a_cmd = false;
		}
		current = current->next;
	}
}

/*This function check if a node has an empty value and set to be removed*/
void	check_empty_nodes(t_token_list **token)
{
	t_token_list	*current;
	int				i;
	bool			is_empty;

	current = *token;
	while (current != NULL)
	{
		if (current->token == WORD || current->token == SQUOTE
			||current->token == DQUOTE)
		{
			i = -1;
			is_empty = true;
			if (ft_strlen(current->value) == 0)
				current->to_remove = true;
			else
				while (current->value[++i] != '\0')
					if (!space(current->value[i]) || (space(current->value[i])
							&& (current->token == DQUOTE
								|| current->token == SQUOTE)))
						is_empty = false;
			if (is_empty == true)
				current->to_remove = true;
		}
		current = current->next;
	}
}
