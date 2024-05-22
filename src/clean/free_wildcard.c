/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:50:50 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/12 16:50:50 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_wildcard_list(t_wildcard *wildcard)
{
	t_wildcard_list		*current;
	t_wildcard_list		*next;

	current = wildcard->list;
	while (current != NULL)
	{
		next = current->next;
		free(current->file);
		free(current);
		current = next;
	}
	wildcard->list = NULL;
}

void	free_wildcard_dirs(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
	return ;
}

void	free_wildcard(t_token_list *current)
{
	while (current)
	{
		if (current->wildcard.has_wildcard)
		{
			free_wildcard_dirs(current->wildcard.dirs);
			free_wildcard_list(&current->wildcard);
		}
		current = current->next;
	}
}

void	free_matches(char **matches)
{
	int	i;

	i = 0;
	while (matches[i] != NULL)
	{
		free (matches[i]);
		i++;
	}
	free (matches);
}
