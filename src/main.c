/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 11:15:05 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/04 16:27:42 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_input_after_managing(t_state *state)
{
	printf("\033[0;32m*** TOKEN LIST ***\n");
	printf("\033[0m");
	token_print_list(state->token_list);
}

int	main(int argc, char **argv, char **envp)
{
	t_state				state;

	init_state(&state, envp, argc, argv);
	init_signal_handlers();
	while (state.run == true)
	{
		rl_replace_line("", 0);
		state.input = readline(get_prompt(&state));
		if (state.input == NULL)
			break ;
		else if (ft_strlen(state.input) != 0 && !is_empty(state.input))
		{
			state.input = is_not_terminated(state.input, &state);
			add_history(state.input);
			manage_input(&state);
			if (state.error == false)
				execute_tree(&state, 0);
			free_allocation_malloc(&state.token_list, state.input, \
				&state.segments);
		}
	}
	free_allocation_malloc_vars(state.var_list);
	free_allocation_malloc_path_env(state.path_env, &state);
	return (state.command_status);
}
