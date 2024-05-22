/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:26:37 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/11 16:55:57 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Functions that manage the list of infiles and outfiles*/
int	file_lstsize(t_redir *lst)
{
	int				i;
	t_redir			*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*Functions that manage the list of infiles and outfiles*/
void	file_lstadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (lst)
	{
		if (*lst)
		{
			last = file_lstlast(*lst);
			last->next = new;
			last->next->prev = last;
		}
		else
			*lst = new;
	}
}

/*Functions that manage the list of infiles and outfiles*/
t_redir	*file_lstnew(t_token token, char *value, int fd)
{
	t_redir	*lst;

	lst = (t_redir *)malloc(sizeof(t_redir));
	if (!lst)
		ft_malloc_error();
	if (fd == 0)
	{
		lst->fd = -2;
		lst->token = token;
		lst->found = true;
		lst->value = ft_strdup(value);
		lst->next = NULL;
		lst->prev = NULL;
	}
	else if (fd == 1)
	{
		lst->fd = -2;
		lst->token = token;
		lst->found = true;
		lst->value = ft_strdup(value);
		lst->next = NULL;
		lst->prev = NULL;
	}
	return (lst);
}

/*Functions that manage the list of infiles and outfiles*/
t_redir	*file_lstlast(t_redir *lst)
{
	t_redir	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

/*Functions that manage the list of infiles and outfiles*/
void	file_print_list(t_redir *lst)
{
	t_redir	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->token == LESS)
			printf("FILE IS : < %s\n", current->value);
		else if (current->token == GREAT)
			printf("FILE IS : > %s\n", current->value);
		else if (current->token == DLESS)
			printf("FILE IS : << %s\n", current->value);
		else if (current->token == DGREAT)
			printf("FILE IS : >> %s\n", current->value);
		current = current->next;
	}
}
