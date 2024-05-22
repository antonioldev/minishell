/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:57:24 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:14:21 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env_vars_from_child(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	return ;
}

/*This function assign redirection, close pipes and call execve()*/
void	execute_child(t_state *s, t_token_list *cmd, int i)
{
	t_cmd_exec_status	cmd_status;
	char				*path;
	char				**env_list;

	env_list = NULL;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_redirection(&cmd, &s, i);
	cmd_status = handle_built_in(s, cmd);
	if (cmd_status == COMMAND_EXECUTED)
	{
		free_all_memory(s);
		exit(EXIT_SUCCESS);
	}
	path = my_getenv(s->var_list, "PATH");
	if (path != NULL)
		s->path_env = ft_split(path, ':');
	add_path_to_cmd(cmd, s->path_env);
	close_all_pipes(s);
	env_list = concatenate_key_value(s->var_list, var_lstsize(s->var_list));
	execve(cmd->path, cmd->args, env_list);
	free_env_vars_from_child(env_list);
	exit(error_exceve(cmd->args[0], s));
}

/*This function save the outfile of pipe for next command
	and wait for child process*/
void	execute_parent(t_state *s, t_token_list *cmd, int i)
{
	int	stat_loc;
	int	j;
	int	exit_status;

	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, SIG_IGN);
	close(s->pipes[i][1]);
	s->prev_pipe = s->pipes[i][0];
	if (i == s->number_commands - 1)
		close(s->prev_pipe);
	if (i == s->number_commands - 1)
	{
		waitpid(s->pids[i], &stat_loc, 0);
		if (WIFEXITED(stat_loc))
		{
			exit_status = WEXITSTATUS(stat_loc);
			s->command_status = exit_status;
		}
		j = -1;
		while (++j < i)
			close(s->pipes[j][0]);
	}
	(void)cmd;
}

/*Execution of commands using forks*/
static bool	execute_commands(t_state *state, t_token_list *token_list, int i)
{
	t_token_list	*current;

	allocate_pipe_memory(&state);
	current = token_list;
	while (i < state->number_commands)
	{
		open_fd(current, state);
		if (current->run == true)
		{
			state->pids[i] = fork();
			if (state->pids[i] == -1)
				ft_fork_error();
			if (state->pids[i] == 0)
				execute_child(state, current, i);
			else
				execute_parent(state, current, i);
		}
		current = current->next;
		i++;
	}
	i = 0;
	while (i++ < state->number_commands - 1)
		wait(NULL);
	free_allocation_malloc_pipes(state);
	return (true);
}

/*Function that execute each branch of the tree*/
void	execute_tree(t_state *s, int i)
{
	t_token_list	*current;

	while (s->segments[i] != NULL && s->run == true)
	{
		current = s->segments[i];
		if (current->token == LOGICAL_OR && s->command_status == 0)
			i = advance_and_skip_parentheses(s, i);
		else if (current->token == LOGICAL_AND && s->command_status != 0)
			i = advance_and_skip_parentheses(s, i);
		else if (current->type == CMD)
		{
			s->number_commands = count_nodes(current);
			if (is_solo_and_built_in(current, s->number_commands) == true)
				s->command_status = handle_built_in(s, current);
			else
				s->run = execute_commands(s, current, 0);
		}
		i++;
	}
	signal(SIGINT, sigint_handler);
}
