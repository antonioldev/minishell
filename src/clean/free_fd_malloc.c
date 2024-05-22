/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fd_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:48:16 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:48:16 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function calls all functions to free memory allocated*/
void	free_all_memory(t_state *s)
{
	free_allocation_malloc(&s->token_list, s->input, &s->segments);
	s->token_list = NULL;
	s->input = NULL;
	free_allocation_malloc_pipes(s);
	free_allocation_malloc_vars(s->var_list);
	s->var_list = NULL;
	free_allocation_malloc_path_env(s->path_env, s);
	s->path_env = NULL;
	free(s->segments);
	s->segments = NULL;
}

/*Free all memory allocated with malloc for infile and outfile*/
void	free_redirection(t_redir **infile, t_redir **outfile)
{
	t_redir	*current;
	t_redir	*temp;

	current = *infile;
	while (current != NULL)
	{
		if (current->fd > 2)
			close (current->fd);
		free (current->value);
		temp = current->next;
		free (current);
		current = temp;
	}
	*infile = NULL;
	current = *outfile;
	while (current != NULL)
	{
		if (current->fd > 2)
			close (current->fd);
		free (current->value);
		temp = current->next;
		free (current);
		current = temp;
	}
	*outfile = NULL;
}

/*This function free the memory for temporary env variables*/
void	free_temporary_vars(char **key, char **value)
{
	free (*key);
	free (*value);
	*key = NULL;
	*value = NULL;
}

/*This function free the path_env variable*/
void	free_allocation_malloc_path_env(char **path_env, t_state *s)
{
	int	i;

	i = 0;
	if (path_env == NULL)
		return ;
	while (path_env[i] != NULL)
	{
		free (path_env[i]);
		i++;
	}
	free (path_env);
	close (s->null_fd);
}

void	free_allocation_malloc_pipes(t_state *state)
{
	int	i;

	i = 0;
	while (i < (*state).number_commands)
	{
		free((*state).pipes[i]);
		i++;
	}
	free((*state).pipes);
	(*state).pipes = NULL;
	free((*state).pids);
	(*state).pids = NULL;
}
