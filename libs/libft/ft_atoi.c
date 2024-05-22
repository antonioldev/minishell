/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:50:21 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:50:22 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespace(const char *nptr, int i)
{
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	return (i);
}

int	parse_sign(const char *nptr, int i, int *neg)
{
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*neg = 1;
		i++;
	}
	return (i);
}

int	parse_quotes(const char *nptr, int i, int *in_quotes)
{
	if (nptr[i] == '\"' || nptr[i] == '\'')
	{
		*in_quotes = 1;
		i++;
	}
	return (i);
}

int	parse_digits(const char *nptr, int i, int *result, int *in_quotes)
{
	while (nptr[i] != '\0')
	{
		if (*in_quotes && (nptr[i] == '\"' || nptr[i] == '\''))
		{
			*in_quotes = 0;
			i++;
			continue ;
		}
		if (!in_quotes && (nptr[i] == '\"' || nptr[i] == '\''))
			return (0);
		if (!ft_isdigit(nptr[i]))
			return (0);
		*result = (*result) * 10 + (nptr[i] - '0');
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr, int i)
{
	int	neg;
	int	result;
	int	in_quotes;

	neg = 0;
	result = 0;
	in_quotes = 0;
	i = skip_whitespace(nptr, i);
	i = parse_sign(nptr, i, &neg);
	i = parse_quotes(nptr, i, &in_quotes);
	i = parse_digits(nptr, i, &result, &in_quotes);
	if (in_quotes)
		return (0);
	if (neg)
		result = -1 * result;
	return (result);
}
