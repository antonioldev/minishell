/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alimotta <alimotta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 08:50:27 by alimotta          #+#    #+#             */
/*   Updated: 2024/05/22 08:50:28 by alimotta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	int			check;
	const char	*ptr;

	i = 0;
	check = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			ptr = &s[i];
			check = 1;
		}
		i++;
	}
	if (s[i] == (char)c)
	{
		ptr = &s[i];
		check = 1;
	}
	if (check == 1)
		return ((char *)ptr);
	else
		return (NULL);
}
/*int 	main()
{
	char * s = "CiaoY mi chiamo Antonio";
	char c ;
	char *j ;
	char *y;
	j = strrchr (s, c);
	if (j)
		printf("%p\n", j);
	y = ft_strrchr(s, c);
	if (y)
		printf("%p\n", y);
	return (0);


}*/
