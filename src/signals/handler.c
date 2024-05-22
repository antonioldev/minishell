/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:33:47 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:00:45 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Signal handler for SIGINT (Ctrl+C)*/
void	sigint_handler(int signum)
{
	if (signum)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_child_handler(int signum)
{
	if (signum)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

/*Signal handler for SIGQUIT (Ctrl+D)*/
void	sigquit_handler(int signum)
{
	if (signum != 3)
		return ;
}

void	heredoc_sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		signal(SIGQUIT, SIG_DFL);
		raise(SIGQUIT);
	}
}

/*Function that handles the signals*/
void	init_signal_handlers(void)
{
	printf("\033[?12h");
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGQUIT, SIG_IGN);
}
