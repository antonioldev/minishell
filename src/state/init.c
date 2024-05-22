/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:12:25 by vsouza-v          #+#    #+#             */
/*   Updated: 2024/05/04 16:26:37 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_env_vars(t_state *s, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	**var;
	int		j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = -1;
		var = ft_split(envp[i], '=');
		key = var[0];
		value = getenv(key);
		if (value)
			var_lstadd_back(&s->var_list, var_lstnew(key, value));
		else
			var_lstadd_back(&s->var_list, var_lstnew(key, ""));
		while (var[++j] != NULL)
			free(var[j]);
		free(var);
		i++;
	}
	return ;
}

/*This function look for the variable in the envp array*/
char	*my_getenv(t_var_list *head, char *env)
{
	t_var_list	*current;

	current = head;
	while (current != NULL)
	{
		if (strncmp(current->key, env, 5) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/*Initiate some data from the state struct*/
void	init_state(t_state *state, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	state->var_list = NULL;
	state->command_status = 0;
	state->token_list = NULL;
	state->path_env = NULL;
	state->segments = NULL;
	state->number_commands = 0;
	state->run = true;
	state->error = false;
	state->prev_pipe = -1;
	state->original_stdin = dup(STDIN_FILENO);
	state->original_stdout = dup(STDOUT_FILENO);
	state->null_fd = open("/dev/null", O_RDONLY);
	state->num_segments = 0;
	if (envp)
		init_env_vars(state, envp);
}
