/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:04:30 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/23 01:28:40 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = 0;
	while (*s)
	{
		if (*s && *s == (char )c)
			last = s;
		s++;
	}
	if ((char )c == '\0')
		return ((char *)s);
	return ((char *)last);
}

/*#include <stdio.h>

int	main(void)
{
	const char	*str = "banana";
	char		*result = ft_strrchr(str, 'b');

	if (result)
	{
		printf("Última ocorrência de 'a': %s\n", result);
	}
	else
	{
		printf("Caractere não encontrado.\n");
	}
	return (0);
}*/
