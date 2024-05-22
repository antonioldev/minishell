/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:06:15 by vsouza-v          #+#    #+#             */
/*   Updated: 2024/05/19 11:12:16 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Check if there are any duplicates in the variables list*/
void	find_duplicate_var(t_var_list **head_env_var)
{
	size_t		len_current;
	size_t		len_temp;
	t_var_list	*temp;
	t_var_list	*current;

	current = *head_env_var;
	while (current != NULL)
	{
		len_current = ft_strlen(current->key);
		temp = current;
		while (temp != NULL)
		{
			len_temp = ft_strlen(temp->key);
			if ((temp != current) && (len_current == len_temp)
				&& ft_strncmp(current->key, temp->key, len_current) == 0)
				current->to_remove = true;
			temp = temp->next;
		}
		current = current->next;
	}
}

/*Check if the charachter is '=' */
bool	find_equal(char *str, int *pos)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			*pos = i;
			return (true);
		}
		i++;
	}
	return (false);
}

/*If it find a variable, it create a new node to the variables list*/
void	create_key_and_value(char *str, char **key,
	char **value, int pos_equal)
{
	int	start;
	int	end;

	start = pos_equal - 1;
	while (start > 0 && (ft_isalnum(str[start]) || str[start] == '_'))
		start--;
	if (ft_isdigit(str[start]))
	{
		*key = NULL;
		*value = NULL;
	}
	else
	{
		*key = ft_substr(str, start, pos_equal - start);
		end = pos_equal + 1;
		while (str[end] != '\0' && !space(str[end]))
			end++;
		if (end > pos_equal)
			*value = ft_substr(str, pos_equal + 1, end - pos_equal);
		else
			*value = ft_strdup("");
	}
}

/*This function check if we assign a value to a variable*/
t_var_list	*find_env_vars(t_token_list **head_token,
	t_var_list *head_vars, char *key, char *value)
{
	t_token_list	*current_token;
	t_var_list		*current_env_var;
	int				pos;

	current_token = *head_token;
	current_env_var = head_vars;
	while (current_token != NULL)
	{
		pos = -1;
		if (current_token->token == WORD
			&& find_equal(current_token->value, &pos))
		{
			if (pos != -1 || pos != 0)
				create_key_and_value(current_token->value, &key, &value, pos);
			if (key != NULL)
			{
				var_lstadd_back(&current_env_var, var_lstnew(key, value));
				free_temporary_vars(&key, &value);
				current_token->to_remove = true;
			}
		}
		current_token = current_token->next;
	}
	return (current_env_var);
}
