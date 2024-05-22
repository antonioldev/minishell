/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:46:32 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/02 10:24:52 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function works as per linux isspace()*/
bool	space(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/*This function return true if char is an operator*/
static bool	operator(int c)
{
	if (c == PIPE || c == LESS || c == DLESS || c == DGREAT || c == '&'
		|| c == GREAT || c == O_PARENTHESIS || c == C_PARENTHESIS)
		return (true);
	return (false);
}

/*This function find a string and return it*/
char	*find_str(char *str, size_t *i, t_token token)
{
	size_t	start;
	size_t	index;
	char	*word;

	start = *i;
	index = 0;
	if ((char)token == WORD)
		while (!space((int)str[*i]) && !operator((int)str[*i])
			&& str[*i] != '\0')
			(*i)++;
	else
	{
		start++;
		while (str[++(*i)] != (char)token)
			;
	}
	word = malloc((char)(*i - start + 2) * sizeof(char));
	if (!word)
		ft_malloc_error();
	while (start < *i)
		word[index++] = str[start++];
	word[index] = '\0';
	if (token == WORD)
		(*i)--;
	return (word);
}
