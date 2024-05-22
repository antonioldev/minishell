/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_structure.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:58:10 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/02 10:25:25 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function return TRUE if redirection is < or <<*/
static bool	is_in_redirection(t_token_list *prev)
{
	if (prev->token == DLESS || prev->token == LESS)
		return (true);
	return (false);
}

/*This function return TRUE if redirection is > or >>*/
static bool	is_out_redirection(t_token_list *prev)
{
	if (prev->token == DGREAT || prev->token == GREAT)
		return (true);
	return (false);
}

/*Checking if the token is an operator*/
static bool	is_operator(t_token_list *current)
{
	if (current->token == DLESS || current->token == LESS
		|| current->token == DGREAT || current->token == GREAT
		|| current->token == PIPE)
		return (true);
	return (false);
}

/*Checking if the token is && || or ()*/
static bool	is_complex_operator(t_token_list *current)
{
	if (current->token == LOGICAL_AND || current->token == LOGICAL_OR
		|| current->token == O_PARENTHESIS || current->token == C_PARENTHESIS)
		return (true);
	return (false);
}

/*Checking if the token is a command, an argument or an operator*/
void	set_command_structure(t_state **state, bool found_cmd)
{
	t_token_list	*current;

	current = (*state)->token_list;
	while (current != NULL)
	{
		if (is_operator(current))
			current->type = OPERATOR;
		else if (is_complex_operator(current))
			current->type = COMPLEX_CMD;
		else if (current->prev != NULL && is_in_redirection(current->prev))
			current->type = INFILE;
		else if (current->prev != NULL && is_out_redirection(current->prev))
			current->type = OUTFILE;
		else if (found_cmd == true)
			current->type = ARG;
		else
		{
			current->type = CMD;
			found_cmd = true;
		}
		if (current->token == PIPE || is_complex_operator(current))
			found_cmd = false;
		current = current->next;
	}
}
