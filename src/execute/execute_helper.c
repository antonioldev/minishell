/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:48:45 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:48:47 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Count how many nodes are in each segment*/
int	count_nodes(t_token_list *current)
{
	int	i;

	i = 0;
	while (current != NULL)
	{
		i++;
		if (current->is_last == true)
			break ;
		current = current->next;
	}
	return (i);
}

/*Helper function to handle the advancement and parentheses traversal*/
int	advance_and_skip_parentheses(t_state *s, int i)
{
	t_token_list	*current;

	i++;
	current = s->segments[i];
	if (current->token == O_PARENTHESIS)
	{
		while (current->token != C_PARENTHESIS)
			current = s->segments[++i];
	}
	return (i);
}

char	**concatenate_key_value(t_var_list *list, int size)
{
	char		**result;
	t_var_list	*temp;
	int			i;

	result = (char **)malloc((size + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	temp = list;
	i = 0;
	while (temp)
	{
		size = ft_strlen(temp->key) + ft_strlen(temp->value) + 1;
		result[i] = (char *)malloc((size + 1) * sizeof(char));
		if (!result[i])
		{
			free(result);
			return (NULL);
		}
		ft_strlcpy(result[i], temp->key, size);
		ft_strlcat(result[i], "=", size);
		ft_strlcat(result[i++], temp->value, size + 1);
		temp = temp->next;
	}
	result[i] = NULL;
	return (result);
}
