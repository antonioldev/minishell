/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:09:39 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/15 16:09:39 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_dirs_count(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
		i++;
	return (i);
}

static void	handle_single_dir(t_token_list *current, int *i)
{
	current->wildcard.dirs = (char **)malloc(3 * sizeof(char *));
	current->wildcard.dirs[0] = ft_strdup(".");
	current->wildcard.dirs[1] = ft_strdup(current->value);
	current->wildcard.dirs[2] = '\0';
	(*i) = 2;
	return ;
}

void	handle_wildcard(t_token_list *current)
{
	char	*wildcard;
	char	**dirs;
	int		n_dirs;

	while (current != NULL && current->token != PIPE
		&& current->type != COMPLEX_CMD)
	{
		wildcard = ft_strchr(current->value, '*');
		if (wildcard != NULL)
		{
			dirs = ft_split(current->value, '/');
			n_dirs = get_dirs_count(dirs);
			if (n_dirs == 1)
			{
				free_wildcard_dirs(dirs);
				handle_single_dir(current, &n_dirs);
			}
			else
				current->wildcard.dirs = dirs;
			current->wildcard.n_dirs = n_dirs - 1;
			current->wildcard.has_wildcard = true;
		}
		current = current->next;
	}
	return ;
}

int	build_wildcard_list_loop(t_token_list *c, int i, int len, t_obj *obj)
{
	i = 0;
	obj->object = readdir(obj->dir);
	while (obj->object != NULL)
	{
		if (obj->object->d_name[0] == '.')
			obj->object = readdir(obj->dir);
		obj->new_path = build_path(obj->path, obj->object->d_name);
		if (i + 1 == len)
		{
			if (match_pattern(c->wildcard.dirs[i + 1], obj->object->d_name))
			{
				obj->n_objects++;
				wildcard_lstadd_back(&c->wildcard.list, \
				wildcard_lstnew(ft_strdup(obj->new_path)));
			}
		}
		else if (obj->object->d_type == DT_DIR
			&& match_pattern(c->wildcard.dirs[i + 1], obj->object->d_name))
			obj->n_objects += build_wildcard_list(c, i + 1, len, obj->new_path);
		free(obj->new_path);
		obj->object = readdir(obj->dir);
	}
	return (obj->n_objects);
}

int	build_wildcard_list(t_token_list *c, int i, int len, char *path)
{
	t_obj	obj;

	if (i >= len)
		return (0);
	obj.dir = opendir(path);
	if (!obj.dir)
		return (0);
	obj.n_objects = 0;
	obj.path = path;
	obj.n_objects = build_wildcard_list_loop(c, i, len, &obj);
	closedir(obj.dir);
	return (obj.n_objects);
}
