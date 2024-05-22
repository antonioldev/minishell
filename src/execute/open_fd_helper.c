/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 09:54:12 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:24:37 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] == '\n' && s2[i] == '\0')
			return (0);
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2 [i]);
		i++;
	}
	return (0);
}

static int	pattern_match(const char *pattern, const char *str)
{
	while (*pattern && *str)
	{
		if (*pattern == '*')
		{
			pattern++;
			if ((*pattern) == '\0')
				return (1);
			while (*str)
			{
				if (pattern_match(pattern, str++))
					return (1);
			}
			return (0);
		}
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else
			return (0);
	}
	if (*pattern == '*')
		pattern++;
	return (*pattern == '\0' && *str == '\0');
}

static int	expand_wildcard(const char *pattern, char ***matches,
	char *dir_path, int count)
{
	DIR				*dir;
	struct dirent	*entry;

	*matches = malloc(3 * sizeof(char *));
	if (*matches == NULL)
		ft_malloc_error();
	dir = opendir(dir_path);
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL && count < 3)
	{
		if (pattern_match(pattern, entry->d_name))
		{
			(*matches)[count] = strdup(entry->d_name);
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	(*matches)[count] = NULL;
	return (count);
}

int	check_wildcard_files(char **file_name)
{
	char	**matches;
	int		n_matches;

	matches = NULL;
	if (*file_name[0] == '*')
		return (-1);
	else if (ft_strchr(*file_name, '*') == NULL)
		return (0);
	else
	{
		n_matches = expand_wildcard(*file_name, &matches, ".", 0);
		if (n_matches > 1)
			return (free_matches(matches), -1);
		else if (n_matches == 1)
		{
			free (*file_name);
			*file_name = ft_strdup(matches[0]);
		}
		free_matches(matches);
	}
	return (0);
}

/*This function set the command run to false and print the error for infile*/
void	set_cmd_run_false(t_token_list **cmd, char *value)
{
	(*cmd)->run = false;
	perror(value);
}
