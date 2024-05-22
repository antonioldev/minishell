/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:49:04 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:49:05 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	count_commands(t_state **state)
{
	t_token_list	*current;

	current = (*state)->token_list;
	while (current != NULL)
	{
		if (current->type == CMD)
			(*state)->number_commands++;
		current = current->next;
	}
}

/*This function check if the input contains only whitespaces*/
bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!space(str[i]))
			return (false);
		i++;
	}
	free (str);
	str = NULL;
	return (true);
}

void	manage_input(t_state *state)
{
	if (state->error == true)
		return ;
	state->number_commands = 0;
	state->token_list = tokenize(state->input, ft_strlen(state->input));
	replace_env_vars(&state->token_list, state->var_list,
		0, state->command_status);
	check_empty_nodes(&state->token_list);
	token_remove_unwanted_nodes(&state->token_list);
	set_command_structure(&state, false);
	ensure_cmd_between_pipes(state->token_list);
	find_redirections(&state);
	if (state->error == true)
		return ;
	token_remove_unwanted_nodes(&state->token_list);
	create_args_array(&state);
	free_wildcard(state->token_list);
	check_sintax_input(state->token_list, state);
	remove_pipes_and_args(&state->token_list);
	token_remove_unwanted_nodes(&state->token_list);
	count_commands(&state);
	split_list(state->token_list, &state->segments, &state->num_segments, 0);
}
