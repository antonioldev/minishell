/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 06:50:23 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/18 12:45:25 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function get the prompt name used by getline()*/
char	*get_prompt(t_state *state)
{
	char	*color_prefix;
	char	*color_suffix;

	set_cwd(state);
	if (state->command_status == 0)
		color_prefix = "\001\033[32m\002";
	else
		color_prefix = "\001\033[31m\002";
	color_suffix = "\001\033[0m\002";
	ft_strlcpy(state->prompt, color_prefix, sizeof(state->prompt));
	strcat(state->prompt, color_prefix);
	strcat(state->prompt, "-> ");
	strcat(state->prompt, "\001\033[36m\002");
	strcat(state->prompt, state->cwd);
	strcat(state->prompt, color_suffix);
	strcat(state->prompt, " ");
	return (state->prompt);
}

// GREEN, with readline non-printing markers
// RED, with readline non-printing markers
// RESET, with readline non-printing markers
// CYAN, with readline non-printing markers