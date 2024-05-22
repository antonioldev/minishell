/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:24:29 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/03 16:46:29 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_fd_solo_command(t_state *s, t_token_list *cmd)
{
	int	original_stdout;

	original_stdout = dup(STDOUT_FILENO);
	if (s->number_commands == 1)
	{
		open_fd(cmd, s);
		if (cmd->run == false)
			return (-2);
		if (cmd->fd_out != STDOUT_FILENO)
			dup2(cmd->fd_out, STDOUT_FILENO);
	}
	return (original_stdout);
}

/*Function that manage the built in functions*/
t_cmd_exec_status	handle_built_in(t_state *s, t_token_list *cmd)
{
	if (!s || !s->token_list)
		return (COMMAND_EXECUTED);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (handle_cd_cmd(s, cmd));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (handle_pwd_cmd(s, cmd));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (handle_env_cmd(s, cmd));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (handle_export(s, cmd));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (handle_unset_cmd(s, cmd));
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (handle_echo_cmd(s, cmd));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (handle_exit_cmd(s, cmd));
	return (RELEASE_TO_EXEC);
}

/*Check if it's only one command and if that command is built in*/
bool	is_solo_and_built_in(t_token_list *current, int n_commands)
{
	bool			is_built_in;

	is_built_in = false;
	if (n_commands == 1)
	{
		if (ft_strncmp(current->args[0], "cd", 3) == 0)
			is_built_in = true;
		if (ft_strncmp(current->args[0], "pwd", 4) == 0)
			is_built_in = true;
		if (ft_strncmp(current->args[0], "env", 4) == 0)
			is_built_in = true;
		if (ft_strncmp(current->args[0], "export", 7) == 0)
			is_built_in = true;
		if (ft_strncmp(current->args[0], "unset", 6) == 0)
			is_built_in = true;
		if (ft_strncmp(current->args[0], "echo", 5) == 0)
			is_built_in = true;
		if (ft_strncmp(current->args[0], "exit", 5) == 0)
			is_built_in = true;
	}
	return (is_built_in);
}
