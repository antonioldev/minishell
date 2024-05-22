/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:22:01 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/04 16:10:04 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function delete a node from variable list if duplicate*/
void	delete_env_var(t_var_list **list, char *key)
{
	t_var_list	*current;

	current = *list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (current->prev)
				current->prev->next = current->next;
			if (current->next)
				current->next->prev = current->prev;
			if (current == *list)
				*list = current->next;
			if (current->key)
				free (current->key);
			if (current->value)
				free (current->value);
			free(current);
			return ;
		}
		current = current->next;
	}
}
