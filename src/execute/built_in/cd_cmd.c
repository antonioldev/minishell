/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:24:53 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/03 14:58:08 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Check if HOME variable is set in env list*/
char	*find_home_var(t_state *s)
{
	t_var_list	*current;

	current = s->var_list;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		if (ft_strncmp(current->key, "HOME", 5) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	number_of_arguments(t_token_list *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i] != NULL)
		i++;
	return (i);
}

/*Built in to change directory*/
t_cmd_exec_status	handle_cd_cmd(t_state *s, t_token_list *cmd)
{
	char	*dir;
	char	*home;
	int		original_stdout;
	int		num_args;

	dir = cmd->args[1];
	original_stdout = open_fd_solo_command(s, cmd);
	dup2(original_stdout, STDOUT_FILENO);
	if (original_stdout == -2)
		return (COMMAND_FAILED);
	num_args = number_of_arguments(cmd);
	if (num_args > 2)
		return (write(2, "cd: too many arguments\n", 24), COMMAND_FAILED);
	if (num_args == 1)
	{
		home = find_home_var(s);
		if (home == NULL)
			return (write(2, "cd: HOME not set\n", 18), COMMAND_FAILED);
		else
			return (chdir(home), COMMAND_EXECUTED);
	}
	else if (chdir(dir) != 0)
		return (write(2, "cd: No such file or directory\n", 31),
			COMMAND_FAILED);
	return (COMMAND_EXECUTED);
}
