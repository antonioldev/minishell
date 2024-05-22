/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_vars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 07:36:57 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/17 15:55:34 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*manipulate the string from token list, removing the $var and replace it with
	value of the matching key*/
static char	*create_new_word(char *word, char *var, char *to_replace, int start)
{
	int		i;
	int		j;
	char	*new_word;

	i = -1;
	j = 0;
	new_word = (char *)malloc((ft_strlen(word) + ft_strlen(to_replace)
				- ft_strlen(var) + 1) * sizeof(char));
	if (!new_word)
		return (word);
	while (++i < start)
		new_word[i] = word[i];
	while (to_replace[j] != '\0')
		new_word[i++] = to_replace[j++];
	j = ft_strlen(var) + start;
	if (ft_strncmp(var, "$?", ft_strlen(var)) != 0)
		j++;
	while (word[j] != '\0')
		new_word[i++] = word[j++];
	new_word[i] = '\0';
	free (word);
	free (to_replace);
	return (new_word);
}

/*Comparing the string after $ char with key value in the vars list
	and returning a string with the value of the key*/
static char	*replace_dollar_sign(char *var, t_var_list *head_vars, int status)
{
	char		*to_replace;
	t_var_list	*current_vars;

	to_replace = NULL;
	if (ft_strncmp(var, "$?", ft_strlen(var)) == 0)
	{
		to_replace = ft_itoa(status);
		return (to_replace);
	}
	current_vars = head_vars;
	while (current_vars != NULL)
	{
		if ((ft_strlen(var) == ft_strlen(current_vars->key))
			&& ft_strncmp(var, current_vars->key, ft_strlen(var)) == 0)
			to_replace = ft_strdup(current_vars->value);
		current_vars = current_vars->next;
	}
	if (to_replace == NULL)
		to_replace = ft_strdup("");
	return (to_replace);
}

/*serching for the $ char and returning its position*/
static int	find_dollar_sign(char *word, char **var, int i)
{
	int		start;
	int		end;

	while (word[++i] != '\0')
	{
		if (word[i + 1] != '\0' && word[i] == '$' && word[i + 1] == '?')
		{
			*var = ft_strdup("$?");
			return (i);
		}
	}
	i = -1;
	start = -1;
	while (word[++i] != '\0')
		if (word[i] == '$' && word[i + 1] != '\0' && (word[i + 1] == '_'
				|| ft_isalpha(word[i + 1]) || word[i + 1] == '?'))
			start = i + 1;
	end = start;
	if (start != -1)
	{
		while (ft_isalnum(word[end]) || word[end] == '_')
			end++;
		*var = ft_substr(word, start, end - start);
	}
	return (--start);
}

/*Looking for $ sign to count how many time we loop to replace variables*/
static int	find_how_many_dollar_sign(char *word)
{
	int	index;
	int	count;

	index = -1;
	count = 0;
	while (word[++index] != '\0')
		if (word[index] == '$' && word[index + 1] != '\0'
			&& (word[index + 1] == '_' || ft_isalpha(word[index + 1])
				|| word[index + 1] == '?'))
			count++;
	return (count);
}

/*Serching for $ token and replace it with the content of a variable*/
void	replace_env_vars(t_token_list **head_token, t_var_list *head_vars,
			int count, int status)
{
	int				i;
	char			*var;
	t_token_list	*cur_token;

	cur_token = *head_token;
	while (cur_token != NULL)
	{
		var = NULL;
		if (cur_token->token == WORD || cur_token->token == DQUOTE)
		{
			count = find_how_many_dollar_sign(cur_token->value);
			while (count-- > 0)
			{
				i = find_dollar_sign(cur_token->value, &var, -1);
				if (i >= 0)
					cur_token->value = create_new_word(cur_token->value, var,
							replace_dollar_sign(var, head_vars, status), i);
				if (var)
					free(var);
			}
		}
		cur_token = cur_token->next;
	}
}
