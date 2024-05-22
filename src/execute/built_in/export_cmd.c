/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 08:25:06 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/19 11:49:11 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*check_for_quotes(char **arg, int end, int start)
{
	char	*value;
	char	*temp;

	if (arg[1][start] == '\"' || arg[1][start] == '\'')
	{
		temp = ft_strjoin(arg[1], arg[2]);
		value = ft_substr(temp, 1, ft_strlen(temp) - 2);
		free (temp);
	}
	else
		value = ft_substr(arg[1], start, end - start);
	return (value);
}

/*Check if the charachter is '=' */
static bool	find_equal(char *str, int *pos, t_state *s)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			*pos = i;
			return (true);
		}
		i++;
	}
	if (str[i - 1] == '-')
		s->command_status = 1;
	return (false);
}

/*If it find a variable, it create a new node to the variables list*/
static int	create_key_and_value_export(char **arg, char **key,
	char **value, int pos_equal)
{
	int	start;
	int	end;

	start = pos_equal - 1;
	while (start > 0 && (ft_isalnum(arg[1][start]) || arg[1][start] == '_'))
		start--;
	if (start != 0)
	{
		*key = NULL;
		*value = NULL;
		return (1);
	}
	else
	{
		*key = ft_substr(arg[1], start, pos_equal - start);
		end = pos_equal + 1;
		while (arg[1][end] != '\0')
			end++;
		if (end > pos_equal)
			*value = check_for_quotes(arg, end, pos_equal + 1);
		else
			*value = ft_strdup("");
		return (0);
	}
}

/*This function check if we assign a value to a variable*/
static t_var_list	*find_export_vars(t_token_list *cmd,
	t_state *s, char *key, char *value)
{
	t_var_list		*current_env_var;
	int				i;
	int				pos;

	i = 0;
	current_env_var = s->var_list;
	while (cmd->args[++i] != NULL)
	{
		pos = -1;
		if (ft_isdigit (cmd->args[i][0]))
			s->command_status = 1;
		else if (find_equal(cmd->args[i], &pos, s))
		{
			if (pos != -1 || pos != 0)
				s->command_status = \
				create_key_and_value_export(cmd->args, &key, &value, pos);
			if (key != NULL)
			{
				var_lstadd_back(&current_env_var, var_lstnew(key, value));
				free_temporary_vars(&key, &value);
			}
		}
	}
	return (current_env_var);
}

/*Built in to use the export command*/
t_cmd_exec_status	handle_export(t_state *s, t_token_list *cmd)
{
	s->command_status = 0;
	if (cmd->args[1] == NULL)
		print_all_env_vars(s->var_list);
	else
	{
		s->var_list = find_export_vars(cmd, s, NULL, NULL);
		if (s->command_status == 1)
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		token_remove_unwanted_nodes(&s->token_list);
		find_duplicate_var(&s->var_list);
		var_remove_unwanted_nodes(&s->var_list);
	}
	return (s->command_status);
}
