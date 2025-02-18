/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:01:07 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:53:22 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char )c)
		s++;
	if (*s == (char) c)
		return ((char *)s);
	return (0);
}

/*#include <stdio.h>

int	main(void)
{
	char	*word = "Hello, World!";
	int		c = "W";

	printf("%s\n", ft_strchr(word, c));
}*/
