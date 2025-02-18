/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:18:28 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/18 15:32:23 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*p1;
	unsigned const char	*p2;

	p1 = (unsigned const char *)s1;
	p2 = (unsigned const char *)s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}

/*#include <stdio.h>

int	main(void)
{
	char	*str = "Hello, World!";
	char	*str2 = "Hello, Worl";

	printf("%d", ft_memcmp(str, str2, 10));
}*/