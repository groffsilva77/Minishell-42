/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:28:51 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/23 14:04:59 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	n--;
	if ((unsigned char )s1[i] == '\0' || (unsigned char )s2[i] == '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (((unsigned char)s1[i] || (unsigned char)s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*#include <stdio.h>

int	main(void)
{
	char	s1[] = "testing";
	char	s2[] = "tess";

	printf("%i\n", ft_strncmp(s1, s2, 4));
}*/
