/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sintax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:30:34 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/19 16:54:54 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_sintax(char c, t_state *s)
{
	ft_putstr_fd(" syntax error near unexpected token '", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	s->error = true;
	s->command_status = 2;
}

void	check_parenthesis(t_token_list *lst, t_state *s)
{
	if (lst->token == O_PARENTHESIS)
	{
		if (lst->next == NULL)
			print_error_sintax(lst->token, s);
		if (lst->next != NULL && (lst->next->type == COMPLEX_CMD
				|| lst->next->token == PIPE))
			print_error_sintax(lst->next->token, s);
	}
	if (lst->token == C_PARENTHESIS)
	{
		if (lst->prev == NULL)
			print_error_sintax(lst->token, s);
		if (lst->prev != NULL && (lst->prev->type == COMPLEX_CMD
				|| lst->prev->token == PIPE))
			print_error_sintax(lst->prev->token, s);
	}
}

/*Check if the syntax is correct*/
void	check_sintax_input(t_token_list *lst, t_state *s)
{
	while (lst != NULL)
	{
		check_parenthesis(lst, s);
		if (lst->token == LOGICAL_AND || lst->token == LOGICAL_OR)
			if (lst->next != NULL && lst->next->token == PIPE)
				print_error_sintax(lst->next->token, s);
		if (lst->token == PIPE)
			if (lst->next != NULL
				&& (lst->token == LOGICAL_AND || lst->token == LOGICAL_OR))
				print_error_sintax(lst->token, s);
		if (lst->token == LESS || lst->token == GREAT)
			if (lst->next == NULL)
				print_error_sintax(lst->next->token, s);
		lst = lst->next;
	}
}
