/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:59:06 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/21 09:59:06 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Calculate exit status when argument is not in range 0-255*/
static int	calculate_exit_status(int number)
{
	int	status;

	if (number > 255)
		status = number % 256;
	else
	{
		number *= -1;
		status = (256 - number) % 256;
	}
	return (status);
}

/*Check if the argument is a number*/
int	ft_strisnum(const char *str, int i, int in_quotes)
{
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\"' || str[i] == '\'')
	{
		in_quotes = 1;
		i++;
	}
	while (str[i])
	{
		if (in_quotes && (str[i] == '\"' || str[i] == '\''))
		{
			in_quotes = 0;
			i++;
			continue ;
		}
		if ((!in_quotes && (str[i] == '\"' || str[i] == '\''))
			|| (str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	if (in_quotes)
		return (0);
	return (1);
}

// static int	count_args(t_token_list *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->args[i] != NULL)
// 		i++;
// 	i--;
// 	return (i);
// }

/*Built in to use the exit command*/
t_cmd_exec_status	handle_exit_cmd(t_state *s, t_token_list *cmd)
{
	bool	has_more_args;
	int		original_stdout;
	int		status;

	status = 0;
	original_stdout = open_fd_solo_command(s, cmd);
	if (original_stdout == -2)
		return (dup2(original_stdout, STDOUT_FILENO), COMMAND_FAILED);
	dup2(original_stdout, STDOUT_FILENO);
	has_more_args = s->token_list->args[1] != NULL;
	if (has_more_args && s->token_list->args[2] != NULL
		&& ft_strisnum(s->token_list->args[1], 0, 0) != 0)
		return (write(2, "exit\nexit: too many arguments\n", 30), 1);
	else if (has_more_args && ft_strisnum(s->token_list->args[1], 0, 0) == 0)
	{
		s->run = false;
		return (write(2, "exit\nexit: numeric argument required\n", 38), 2);
	}
	else if (s->token_list->args[1])
		status = ft_atoi(s->token_list->args[1], 0);
	if (status < 0 || status > 255)
		status = calculate_exit_status(status);
	s->run = false;
	printf("exit\n");
	return (status);
}
