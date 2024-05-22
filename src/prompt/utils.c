/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 18:15:09 by vsouza-v          #+#    #+#             */
/*   Updated: 2024/05/02 10:29:11 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*If get_current_directory fails, it assign unknow to getline argument*/
void	set_cwd(t_state *state)
{
	if (getcwd(state->cwd, sizeof(state->cwd)) == NULL)
		ft_strlcpy(state->cwd, "Unknown", 8);
}
