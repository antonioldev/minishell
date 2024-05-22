/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:51:09 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/12 16:51:09 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	increment_pointers(char **pattern, char **s)
{
	(*pattern)++;
	(*s)++;
	return ;
}

bool	match_loop(char *pattern, char *str, char *star)
{
	char	*s;

	s = str;
	while (*s)
	{
		if (*pattern == '*')
		{
			star = pattern++;
			if (!*pattern)
				return (true);
		}
		else if (*pattern == *s || *pattern == '?')
			increment_pointers(&pattern, &s);
		else if (star)
		{
			pattern = star + 1;
			str++;
			s = str;
		}
		else
			return (false);
	}
	while (*pattern == '*')
		pattern++;
	return (!*pattern);
}

// Verify if a string match the wildcard pattern, considering the `?`
bool	match_pattern(char *pattern, char *str)
{
	char	*star;

	star = NULL;
	return (match_loop(pattern, str, star));
}

char	*build_path(char *path, char *name)
{
	char	*new_path;
	char	*final_path;

	new_path = ft_strjoin(path, "/");
	final_path = ft_strjoin(new_path, name);
	free(new_path);
	return (final_path);
}
