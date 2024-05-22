/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 08:24:35 by alimotta          #+#    #+#             */
/*   Updated: 2024/04/28 08:24:35 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function set the redirection for each command*/
void	set_redirection(t_token_list **command, t_state **state, int i)
{
	t_state			*s;
	t_token_list	*cmd;

	cmd = *command;
	s = *state;
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	else if (i > 0 && cmd->prev->run == false)
		dup2(s->null_fd, STDIN_FILENO);
	else if (i > 0 && s->prev_pipe >= 0)
		dup2(s->prev_pipe, STDIN_FILENO);
	else
		dup2(s->original_stdin, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->next != NULL && s->pipes[i][1] >= 0 && cmd->is_last == false)
		dup2(s->pipes[i][1], STDOUT_FILENO);
	else
		dup2(s->original_stdout, STDOUT_FILENO);
}
