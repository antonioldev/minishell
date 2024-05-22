/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:47:45 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/19 07:37:23 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*Prints all env when export is used without any options*/
void	print_all_env_vars(t_var_list *vars)
{
	while (vars != NULL)
	{
		printf ("declare -x %s=\"%s\"\n", vars->key, vars->value);
		vars = vars->next;
	}
}
