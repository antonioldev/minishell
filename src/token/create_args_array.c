/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_args_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:49:40 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:49:40 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fill_array_with_wildcard(t_token_list *current, char **args, int i)
{
	t_wildcard_list		*list;
	int					j;

	list = current->wildcard.list;
	j = 0;
	while (list != NULL)
	{
		args[i] = ft_strdup(list->file);
		j++;
		i++;
		list = list->next;
	}
	return (j);
}

/*This function allocate memory and copy each arguments*/
static char	**fill_array_with_arguments(t_token_list *current, int length)
{
	int		i;
	int		n_matches;
	char	**args;

	i = 0;
	args = (char **)malloc((length + 1) * sizeof(char *));
	if (!args)
		ft_malloc_error();
	n_matches = 0;
	while (i < length)
	{
		if (current->wildcard.has_wildcard)
			n_matches = fill_array_with_wildcard(current, args, i);
		if (n_matches > 0)
			i += n_matches;
		else
		{
			args[i] = ft_strdup(current->value);
			i++;
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

/*This function calculate how many arguments are avaible for the command*/
static int	number_of_args_per_command(t_token_list *current)
{
	int	i;
	int	n_matches;

	i = 0;
	while (current != NULL)
	{
		if (current->token == PIPE || current->type == COMPLEX_CMD)
			break ;
		if (current->wildcard.has_wildcard)
		{
			n_matches = build_wildcard_list(current, 0, \
			current->wildcard.n_dirs, current->wildcard.dirs[0]);
			if (n_matches)
				i += n_matches;
			else
				i++;
		}
		else
			i++;
		current = current->next;
	}
	return (i);
}

/*This function create the list of arguments for each command*/
void	create_args_array(t_state **state)
{
	t_token_list	*current;
	int				length;

	current = (*state)->token_list;
	while (current != NULL)
	{
		if (current->type == CMD)
		{
			handle_wildcard(current);
			length = number_of_args_per_command(current);
			current->args = fill_array_with_arguments(current, length);
		}
		current = current->next;
	}
}
