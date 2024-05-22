/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:55:31 by vsouza-v          #+#    #+#             */
/*   Updated: 2024/05/11 15:45:47 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function check if there is a $ sign and return the name of the variable*/
char	*find_dollar(char *str, size_t *i)
{
	size_t	start;
	size_t	index;
	char	*word;

	word = NULL;
	index = 0;
	start = *i;
	(*i)++;
	while (str[*i] == '_' || ft_isalpha(str[*i]))
		(*i)++;
	word = malloc((int)(*i - start + 2) * sizeof(char));
	if (!word)
		ft_malloc_error();
	while (start < *i)
		word[index++] = str[start++];
	word[index] = '\0';
	return (word);
}
