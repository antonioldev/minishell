/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_complex_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 10:42:46 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/15 17:03:57 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function split the list into an array when it found COMPLEX CMD*/
void	split_list(t_token_list *head, t_token_list ***segments,
			int *num, int index)
{
	t_token_list	*current;

	current = head;
	while (current != NULL)
	{
		(*num)++;
		while (current->next != NULL && current->token == current->next->token)
			current = current->next;
		current = current->next;
	}
	*segments = (t_token_list **)malloc((*num + 1) * sizeof(t_token_list *));
	if (*segments == NULL)
		ft_malloc_error();
	current = head;
	index = 0;
	while (current != NULL)
	{
		(*segments)[index++] = current;
		while (current->next != NULL && current->token == current->next->token)
			current = current->next;
		if (current != NULL)
			current->is_last = true;
		current = current->next;
	}
	(*segments)[index] = NULL;
}
