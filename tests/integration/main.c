/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:09:00 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/01 16:04:53 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token_list *lst)
{
	t_token_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->token == WORD || current->token == SQUOTE
			|| current->token == DQUOTE)
			printf("%s\n", current->value);
		else
			printf("%i\n", (int)current->token);
		current = current->next;
	}
}

void	print_list_var(t_token_list *lst)
{
	t_token_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->token == VAR)
		{
			printf("%s = %s\n", current->key, current->value);
		}
		current = current->next;
	}
}

void	free_allocation_malloc(t_token_list *lst, char *str)
{
	t_token_list	*current;
	t_token_list	*temp;

	current = lst;
	while (current != NULL)
	{
		if (current->token == WORD || current->token == VAR
			|| current->token == SQUOTE || current->token == DQUOTE)
			free(current->value);
		if (current->key)
			free(current->key);
		temp = current->next;
		free(current);
		current = temp;
	}
	if (str != NULL)
		free (str);
}

void	remove_unwanted_nodes(t_token_list **head)
{
	t_token_list	*current;
	t_token_list	*next_node;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->to_remove == true)
		{
			if (current->prev != NULL)
				current->prev->next = current->next;
			else
				*head = current->next;
			if (current->next != NULL)
				current->next->prev = current->prev;
			if (current->value != NULL)
				free(current->value);
			free(current);
		}
		current = next_node;
	}
}
// cc mainTEST.c ./src/env_varables_replace.c ./src/env_variables.c ./src/ft_lst_1.c ./src/ft_lst_2.c ./src/tokenize.c
int	main(void)
{
	t_token_list	*head_token;
	t_token_list	*head_vars;

	int i =-1;
	char	*test[20];
	test[0] = "\'hello world\'";
	test[1] = "";
	test[2] = "hello word";
	test[3] = "\"hello world\" z=Z";
	test[4] = ":::::::::::";
	test[5] = "x=XXX";
	test[6] = "y=YYY";
	test[7] = "$x $y";
	test[8] = "$z";
	test[9] = "$xx \'$yy\' \"$yy\"";
	test[10] = "\"hello $x world\"";
	test[11] = "\"Line 1\nLine 2\"";
	test[12] = "\"text with special characters: !@#$^&*()_+-={}[]:;'<>?,./\"";



	//ft_init_signal();
	head_token = NULL;
	head_vars = NULL;
	while (++i < 13)
	{
		printf("\033[1;32m#### TEST %i ####\n", i);
		head_token = ft_tokenize(test[i], ft_strlen(test[i]));
		//testing
		printf("\n\033[1;31m----NODES TOKEN\n");
		print_list(head_token);
		printf("Size : %i\n", ft_lstsize(head_token));
		head_vars = find_env_variables(head_token, head_vars);
		//testing
		printf("\n\033[1;31m----NODES VARS\n");
		print_list_var(head_vars);
		printf("Size : %i\n", ft_lstsize(head_vars));
		remove_unwanted_nodes(&head_token);
		//testing
		replace_env_variables(head_token, head_vars);
		printf("\n\033[1;31m----NODES TOKEN AFTER REMOVING\n");
		print_list(head_token);
		printf("Size : %i\n", ft_lstsize(head_token));
		free_allocation_malloc(head_token, NULL);
		printf("\n\n");
	}
	free_allocation_malloc(head_vars, NULL); //should be moved to signal ctrl+D
	return (0);
}

// print_list(head_token); //$x "$x" '$x' "ciao $x" "ciao $y" "ciao $x ciao"
	// print_list_var(head_vars);