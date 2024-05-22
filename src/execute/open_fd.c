/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:40:16 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:24:27 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function disable the contrl+\ press*/
static void	set_attribute_terminal(struct termios oldt)
{
	struct termios	newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

/*This function is called if << redirection is used, it reads from terminal*/
void	read_from_terminal(t_token_list *cmd, int fd, char *delimiter)
{
	int				buffer_size;
	int				check;
	char			buffer[1024];
	struct termios	oldt;

	signal(SIGQUIT, SIG_IGN);
	tcgetattr(STDIN_FILENO, &oldt);
	set_attribute_terminal(oldt);
	check = 1;
	while (check != 0)
	{
		write (1, "> ", 2);
		buffer_size = read(0, buffer, 1024);
		if (buffer_size < 0)
			continue ;
		buffer[buffer_size] = '\0';
		check = ft_strcmp(buffer, delimiter);
		if (check != 0)
			write (fd, buffer, buffer_size);
	}
	signal(SIGQUIT, SIG_DFL);
	close (fd);
	cmd->fd_in = open(".here_doc", O_RDWR | O_CREAT, 0666);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

/*This function open all the infile
if any of the open() return -1, the command is not running*/
static int	open_infile(t_token_list **command, t_redir **infile)
{
	t_token_list	*cmd;
	t_redir			*in;

	in = *infile;
	cmd = *command;
	while (in != NULL)
	{
		if (in->found == true)
		{
			if (in->token == LESS && check_wildcard_files(&in->value) == -1)
				return (file_wildcard_error(in->value), -1);
			else if (in->token == LESS)
				in->fd = open(in->value, O_RDONLY);
			else
				in->fd = open(".here_doc", O_RDWR | O_CREAT, 0666);
			if (in->fd == -1)
				return (set_cmd_run_false(&cmd, in->value), -1);
			cmd->fd_in = in->fd;
		}
		if (in->token == DLESS)
			read_from_terminal(cmd, in->fd, in->value);
		in = in->next;
	}
	return (0);
}

/*This function open all the outfile*/
static int	open_outfile(t_token_list **cmd, t_redir **outfile)
{
	t_token_list	*command;
	t_redir			*out;

	out = *outfile;
	command = *cmd;
	while (out != NULL)
	{
		if (out->found == true)
		{
			if (out->token == GREAT && check_wildcard_files(&out->value) == -1)
				return (file_wildcard_error(out->value), -1);
			else if (out->token == GREAT)
				out->fd = open(out->value,
						O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				if (out->token == DGREAT)
					out->fd = open(out->value,
							O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (out->fd == -1)
				return (perror(out->value), -1);
		}
		command->fd_out = out->fd;
		out = out->next;
	}
	return (0);
}

/*This Function open all the infile and outile for the command*/
void	open_fd(t_token_list *command, t_state *s)
{
	t_redir	*in;
	t_redir	*out;

	in = command->infile;
	out = command->outfile;
	if (open_infile(&command, &in) == 0)
	{
		if (open_outfile(&command, &out) == -1)
		{
			s->command_status = 1;
			command->run = false;
		}
	}
	else
	{
		s->command_status = 1;
		command->run = false;
	}
}
