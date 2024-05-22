/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_list_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:26:37 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/19 09:52:34 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Functions that manage the list of variables*/
int	var_lstsize(t_var_list *lst)
{
	int			i;
	t_var_list	*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*Functions that manage the list of variables*/
t_var_list	*var_lstnew(char *key, char *value)
{
	t_var_list	*lst;

	lst = (t_var_list *)malloc(sizeof(t_var_list));
	if (!lst)
		ft_malloc_error();
	lst->key = ft_strdup(key);
	lst->value = ft_strdup(value);
	lst->prev = NULL;
	lst->next = NULL;
	lst->to_remove = false;
	return (lst);
}

/*Functions that manage the list of variables*/
t_var_list	*var_lstlast(t_var_list *lst)
{
	t_var_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

/*Functions that manage the list of variables*/
void	var_print_list(t_var_list *lst)
{
	t_var_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

/*Functions that manage the list of variables*/
void	var_lstadd_back(t_var_list **lst, t_var_list *new)
{
	t_var_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = var_lstlast(*lst);
			last->next = new;
			last->next->prev = last;
		}
		else
			*lst = new;
	}
}
