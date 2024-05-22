/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:24:58 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/11 15:49:25 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Built in to use the env command*/
t_cmd_exec_status	handle_env_cmd(t_state *s, t_token_list *cmd)
{
	bool	has_more_args;
	int		original_stdout;

	has_more_args = s->token_list->args[1] != NULL;
	if (!has_more_args)
	{
		original_stdout = open_fd_solo_command(s, cmd);
		if (original_stdout == -2)
			return (COMMAND_FAILED);
		var_print_list(s->var_list);
		dup2(original_stdout, STDOUT_FILENO);
	}
	return (COMMAND_EXECUTED);
}
