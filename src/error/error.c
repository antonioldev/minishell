/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:22:35 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/10 08:26:54 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_exceve(char *str, t_state *s)
{
	int	err_no;
	DIR	*dir;

	write(2, str, ft_strlen(str));
	dir = opendir(str);
	if (dir != NULL)
	{
		err_no = 126;
		write(2, ": Is a directory\n", 18);
	}
	else
	{
		err_no = 127;
		if (str[0] == '.' || str[0] == '/')
			write(2, ": No such file or directory\n", 29);
		else
			write(2, ": command not found\n", 20);
	}
	free_all_memory(s);
	return (err_no);
}

/*Print an error in case redirection is missing from command*/
void	redirection_error(t_token_list *current)
{
	if (current->next == NULL || current->next->is_fake_command)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putchar_fd(current->next->token, 2);
		ft_putstr_fd("'\n", 2);
	}
}

/*Print error in case fork() fails*/
void	ft_fork_error(void)
{
	perror("Fork failed");
	exit(EXIT_FAILURE);
}

/*Print error in case malloc() fails*/
void	ft_malloc_error(void)
{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
}

void	file_wildcard_error(char *file_name)
{
	write(2, "minishell: ", 12);
	write(2, file_name, ft_strlen(file_name));
	write(2, ": ambiguous redirect\n", 22);
}
