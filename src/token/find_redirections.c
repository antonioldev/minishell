/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:10:38 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/02 10:23:24 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_redirection(t_token_list *cmd,
	t_token_list *redirection, int type)
{
	if (type == INFILE)
		file_lstadd_back(&cmd->infile,
			file_lstnew(redirection->token, redirection->next->value, 0));
	else
		file_lstadd_back(&cmd->outfile,
			file_lstnew(redirection->token, redirection->next->value, 1));
	redirection->to_remove = true;
	redirection->next->to_remove = true;
}

/*Once the command is found, this f() assign the redirection to the command*/
static int	assign_redir(t_token_list *redirection, t_token_list **command)
{
	t_token_list	*cmd;

	cmd = *command;
	if (redirection->next != NULL && (redirection->next->token == WORD
			|| redirection->next->token == DQUOTE
			|| redirection->next->token == SQUOTE))
	{
		if (is_infile_redirection(redirection))
		{
			if (redirection->next && redirection->next->is_fake_command)
				return (2);
			handle_redirection(cmd, redirection, INFILE);
		}
		else if (is_outfile_redirection(redirection))
		{
			if (redirection->next && redirection->next->is_fake_command)
				return (2);
			handle_redirection(cmd, redirection, OUTFILE);
		}
		return (0);
	}
	return (2);
}

/*Once a redirection is found, this function serch for the closer command
	to assign the riderction*/
static t_token_list	*find_closer_command(t_token_list *redirection)
{
	t_token_list	*current;

	current = redirection;
	while (current->next != NULL)
	{
		current = current->next;
		if (current->type == CMD || current->token == PIPE
			|| current->type == COMPLEX_CMD)
			break ;
	}
	if (current->type == CMD)
		return (current);
	current = redirection;
	while (current->prev != NULL)
	{
		current = current->prev;
		if (current->type == CMD || current->token == PIPE
			|| current->type == COMPLEX_CMD)
			break ;
	}
	if (current->type == CMD)
		return (current);
	return (NULL);
}

/*Check if there are any redirections*/
void	find_redirections(t_state **state)
{
	t_token_list	*current;
	t_token_list	*command;
	int				error;

	current = (*state)->token_list;
	while (current != NULL)
	{
		if (is_infile_redirection(current) || is_outfile_redirection(current))
		{
			command = find_closer_command(current);
			error = assign_redir(current, &command);
			if (error == 2)
			{
				(*state)->command_status = error;
				redirection_error(current);
				(*state)->error = true;
				break ;
			}
		}
		current = current->next;
	}
}
