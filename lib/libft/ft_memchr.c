/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:32:20 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/22 15:58:52 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*str;

	str = (const char *)s;
	i = 0;
	if (s == NULL && c == 0 && n == 0)
		return (NULL);
	while (i < n)
	{
		if (str[i] == (char )c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>

int	main(void)
{
	char	*str = "Hello, World!";
	char	c = 'l';

	printf("%s\n", (char *)ft_memchr(str, c, 10));
}*/
