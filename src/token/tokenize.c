/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:28:37 by vsouza-v          #+#    #+#             */
/*   Updated: 2024/05/04 12:31:33 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*This function return the token for && and ||*/
static t_token	find_complex_token(char *str, size_t *i)
{
	if (str[*i] == '(')
		return (O_PARENTHESIS);
	else if (str[*i] == ')')
		return (C_PARENTHESIS);
	else if (str[*i] == '|' && str[*i + 1] == '|')
	{
		(*i)++;
		return (LOGICAL_OR);
	}
	else
	{
		(*i)++;
		return (LOGICAL_AND);
	}
}

/*This function return which operator is found*/
static t_token	find_token(char *str, size_t *i)
{
	if (str[*i] == '|')
		return (PIPE);
	else if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i)++;
		return (DLESS);
	}
	else if (str[*i] == '<')
		return (LESS);
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		(*i)++;
		return (DGREAT);
	}
	else
		return (GREAT);
}

/*This function get the string from getline() and parse the data into
	OPERATOR or WORD*/
t_token_list	*tokenize(char *str, size_t length)
{
	size_t			i;
	t_token_list	*head;

	head = NULL;
	i = -1;
	while (++i < length)
	{
		if ((str[i] == '|' && str[i + 1] == '|') || str[i] == '('
			|| str[i] == ')' || (str[i] == '&' && str[i + 1] == '&'))
			token_lstadd_back(&head,
				token_lstnew(find_complex_token(str, &i), NULL));
		else if (str[i] == '|' || str[i] == '<' || str[i] == '>')
			token_lstadd_back(&head, token_lstnew(find_token(str, &i), NULL));
		else if (str[i] == '\'')
			token_lstadd_back(&head, token_lstnew(SQUOTE,
					find_str(str, &i, SQUOTE)));
		else if (str[i] == '\"')
			token_lstadd_back(&head, token_lstnew(DQUOTE,
					find_str(str, &i, DQUOTE)));
		else if (ft_isalnum(str[i]) || str[i] == '-' || str[i] == '='
			|| str[i] == '/' || str[i] == '.' || str[i] == '$' || str[i] == '*')
			token_lstadd_back(&head, token_lstnew(WORD,
					find_str(str, &i, WORD)));
	}
	return (head);
}
