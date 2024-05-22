/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:51:04 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/12 16:51:04 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	wildcard_lstadd_back(t_wildcard_list **lst, t_wildcard_list *new)
{
	t_wildcard_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = wildcard_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

t_wildcard_list	*wildcard_lstnew(char *file_path)
{
	t_wildcard_list	*lst;

	lst = (t_wildcard_list *)malloc(sizeof(t_wildcard_list));
	if (!lst)
		ft_malloc_error();
	lst->file = file_path;
	lst->next = NULL;
	return (lst);
}

t_wildcard_list	*wildcard_lstlast(t_wildcard_list *lst)
{
	t_wildcard_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

void	wildcard_print_list(t_wildcard_list *lst)
{
	t_wildcard_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("FILE IS : %s\n", current->file);
		current = current->next;
	}
}
