/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:49:22 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:49:22 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Functions that manage the list of tokens*/
void	token_lstadd_back(t_token_list **lst, t_token_list *new)
{
	t_token_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = token_lstlast(*lst);
			if (last)
			{
				if (last->value
					&& ft_strncmp("echo", last->value, ft_strlen("echo")) == 0)
				{
					if (new->token == DQUOTE)
						last->d_quote_start = true;
					if (new->token == SQUOTE)
						last->s_quote_start = true;
				}
			}
			last->next = new;
			last->next->prev = last;
		}
		else
			*lst = new;
	}
}

static void	token_lstnew_helper(t_token_list **lst)
{
	(*lst)->prev = NULL;
	(*lst)->next = NULL;
	(*lst)->path = NULL;
	(*lst)->args = NULL;
	(*lst)->wildcard.dirs = NULL;
	(*lst)->wildcard.list = NULL;
	(*lst)->infile = NULL;
	(*lst)->outfile = NULL;
}

/*Functions that manage the list of tokens*/
t_token_list	*token_lstnew(t_token token, char *value)
{
	t_token_list	*lst;

	lst = (t_token_list *)malloc(sizeof(t_token_list));
	if (!lst)
		ft_malloc_error();
	lst->token = token;
	lst->value = value;
	lst->type = INIT;
	lst->wildcard.has_wildcard = false;
	lst->wildcard.n_dirs = 0;
	lst->to_remove = false;
	lst->is_var = false;
	lst->run = true;
	lst->is_last = false;
	lst->fd_in = 0;
	lst->fd_out = 1;
	lst->d_quote_start = false;
	lst->s_quote_start = false;
	token_lstnew_helper(&lst);
	lst->is_fake_command = false;
	return (lst);
}

/*Functions that manage the list of tokens*/
t_token_list	*token_lstlast(t_token_list *lst)
{
	t_token_list	*current;

	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

/*Functions that manage the list of tokens*/
void	token_print_list(t_token_list *lst)
{
	int				i;
	t_token_list	*current;

	current = lst;
	while (current != NULL)
	{
		i = -1;
		if (current->type == CMD)
		{
			if (current->value != NULL)
				printf("CMD found : %s.\n", current->value);
			if (current->args != NULL)
				while (current->args[++i])
					printf("Arguments are %s.\n", current->args[i]);
			if (current->infile != NULL)
				file_print_list(current->infile);
			if (current->outfile != NULL)
				file_print_list(current->outfile);
		}
		else if (current->type == MEM_VAR)
			printf("VAR found : %s.\n", current->value);
		else if (current->type == OPERATOR)
			printf("%i\n", current->token);
		current = current->next;
	}
}
