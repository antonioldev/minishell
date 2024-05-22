/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:50:40 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:50:40 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Built in to use the pwd command*/
t_cmd_exec_status	handle_pwd_cmd(t_state *s, t_token_list *cmd)
{
	char	dir[1024];
	int		original_stdout;

	(void)s;
	if (getcwd(dir, 1024))
	{
		original_stdout = open_fd_solo_command(s, cmd);
		if (original_stdout == -2)
			return (COMMAND_FAILED);
		printf("%s\n", dir);
		dup2(original_stdout, STDOUT_FILENO);
	}
	else
		return (printf("minishell: pwd: error reading directory\n"),
			COMMAND_FAILED);
	s->command_status = 0;
	return (COMMAND_EXECUTED);
}
