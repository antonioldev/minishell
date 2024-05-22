/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:24:15 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/11 15:49:49 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Built in to use the unset command*/
t_cmd_exec_status	handle_unset_cmd(t_state *s, t_token_list *cmd)
{
	int		i;
	int		original_stdout;

	i = 0;
	original_stdout = open_fd_solo_command(s, cmd);
	if (original_stdout == -2)
		return (dup2(original_stdout, STDOUT_FILENO), COMMAND_FAILED);
	dup2(original_stdout, STDOUT_FILENO);
	while (s->token_list->args[i])
		delete_env_var(&s->var_list, s->token_list->args[i++]);
	return (COMMAND_EXECUTED);
}
