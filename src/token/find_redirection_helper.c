/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_redirection_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:06:31 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/21 13:07:47 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function return TRUE if redirection is < or <<*/
bool	is_infile_redirection(t_token_list *current)
{
	if (current->token == DLESS || current->token == LESS)
		return (true);
	return (false);
}

/*This function return TRUE if redirection is > or >>*/
bool	is_outfile_redirection(t_token_list *current)
{
	if (current->token == DGREAT || current->token == GREAT)
		return (true);
	return (false);
}
