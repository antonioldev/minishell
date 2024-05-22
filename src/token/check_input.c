/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:58:49 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/19 16:59:40 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_error_two(char first, char second)
{
	ft_putstr_fd(" syntax error near unexpected token '", 2);
	ft_putchar_fd(first, 2);
	ft_putchar_fd(second, 2);
	ft_putstr_fd("'\n", 2);
}

static void	print_error_one(char first)
{
	ft_putstr_fd(" syntax error near unexpected token '", 2);
	ft_putchar_fd(first, 2);
	ft_putstr_fd("'\n", 2);
}

/*Check if the input starts with special char and print an error*/
void	check_error_sintax(char *str, t_state **s, int i)
{
	char	first;
	char	second;

	while (str[++i] != '\0')
	{
		while (space(str[i]))
			i++;
		if (str[i] != '\0')
		{
			first = str[i++];
			if (first == '|' || first == '&')
			{
				second = str[i];
				if (second == '|' || second == '&')
					print_error_two(first, second);
				else
					print_error_one(first);
				(*s)->command_status = 2;
				(*s)->error = true;
				break ;
			}
			(*s)->error = false;
			return ;
		}
	}
}

static char	*read_line(char	*input, t_state *state)
{
	char	*temp;
	char	*new_input;

	temp = NULL;
	new_input = NULL;
	temp = readline("> ");
	if (temp == NULL)
	{
		state->error = true;
		return (input);
	}
	new_input = ft_strjoin(input, temp);
	free(input);
	free(temp);
	return (new_input);
}

/*Function is called when the input ends in |*/
char	*is_not_terminated(char *input, t_state *state)
{
	int		i;
	char	last_char;
	char	*new_input;

	check_error_sintax(state->input, &state, -1);
	if (state->error == false)
	{
		i = -1;
		while (input[++i] != '\0')
			if (!space(input[i]))
				last_char = input[i];
		if (last_char == '|' || last_char == '&' || last_char == '(')
		{
			new_input = read_line(input, state);
			return (new_input);
		}
	}
	return (input);
}
