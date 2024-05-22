/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path_to_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:29:01 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/04 16:26:57 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Function that check if the command is found in the env paths
if found, it return the full path, otherwise return as path the cmd itself*/
static char	*check_env_path(char *cmd, char **envp)
{
	int		i;
	char	*temp;
	char	*path;

	i = -1;
	while (envp[++i] != NULL)
	{
		temp = ft_strjoin(envp[i], "/");
		path = ft_strjoin(temp, cmd);
		free (temp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	path = ft_strjoin(cmd, "");
	return (path);
}

/*This function check if the string is a path or not*/
static bool	cmd_include_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

/*This function check if command include a backslash or not*/
void	add_path_to_cmd(t_token_list *head, char **envp)
{
	t_token_list	*current;

	current = head;
	if (envp == NULL)
		current->path = ft_strdup(current->value);
	else if (current->type == CMD && !cmd_include_path(current->value))
		current->path = check_env_path(current->value, envp);
	else if (current->type == CMD && cmd_include_path(current->value))
		current->path = ft_strdup(current->value);
}
