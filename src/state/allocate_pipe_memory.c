/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_pipes_memory.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 07:39:44 by alimotta          #+#    #+#             */
/*   Updated: 2024/04/21 07:39:44 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_error(void)
{
	perror("Pipe creation failed");
	exit(EXIT_FAILURE);
}

/*Allocate memory for each command, used during execution*/
void	allocate_pipe_memory(t_state **state)
{
	int		i;
	t_state	*s;

	i = 0;
	s = *state;
	s->pipes = (int **)malloc(s->number_commands * sizeof(int *));
	s->pids = (pid_t *)malloc(s->number_commands * sizeof(pid_t));
	if (!s->pipes || !s->pids)
		ft_malloc_error();
	while (i < s->number_commands)
	{
		s->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!s->pipes[i])
			ft_malloc_error();
		if (pipe(s->pipes[i]) == -1)
			pipe_error();
		i++;
	}
}
