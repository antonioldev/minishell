/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:54:44 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/21 09:54:44 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Utility function to check if a string is a valid -n flag
static bool	is_valid_n_flag(const char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static bool	should_wr(t_token_list *cmd, char c, char *str, int i)
{
	if (!cmd->d_quote_start && c == '\'')
		return (false);
	if (!cmd->s_quote_start && c == '"')
		return (false);
	if (c == '$' && str[i + 1] != '\0')
		return (false);
	if (c == '$' && (!cmd->d_quote_start && !cmd->s_quote_start))
		return (true);
	return (true);
}

// Function to write a string to the output
static void	write_str(t_token_list *cmd, char *str, int i)
{
	bool	in_double_quotes;
	bool	in_single_quotes;
	char	c;

	in_double_quotes = cmd->d_quote_start;
	in_single_quotes = cmd->s_quote_start;
	while (str[i])
	{
		c = str[i];
		if (c == '\"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;
			continue ;
		}
		if (c == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;
			continue ;
		}
		if (should_wr(cmd, c, str, i) || in_double_quotes || in_single_quotes)
			write(1, &c, 1);
		i++;
	}
}

// Function to handle the echo command
t_cmd_exec_status	handle_echo_cmd(t_state *s, t_token_list *cmd)
{
	bool	has_n_flag;
	int		i;
	int		original_stdout;

	has_n_flag = false;
	i = 1;
	original_stdout = open_fd_solo_command(s, cmd);
	if (original_stdout == -2)
		return (dup2(original_stdout, STDOUT_FILENO), (COMMAND_FAILED));
	while (cmd->args[i] != NULL && is_valid_n_flag(cmd->args[i]))
	{
		has_n_flag = true;
		i++;
	}
	while (cmd->args[i] != NULL)
	{
		write_str(cmd, cmd->args[i], 0);
		if (cmd->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!has_n_flag)
		write(1, "\n", 1);
	dup2(original_stdout, STDOUT_FILENO);
	return (COMMAND_EXECUTED);
}
