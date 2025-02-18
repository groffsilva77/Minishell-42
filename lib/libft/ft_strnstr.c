/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:57:53 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/25 14:47:26 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*sub == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		if (str[i] == sub[0])
		{
			while (sub[j] != '\0' && (i + j) < len
				&& sub[j] == str[i + j])
				j++;
			if (sub[j] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>

int	main(void)
{
	char	*s1 = "Going tomorrow";
	char	*s2 = "to";

	printf("%s\n", ft_strnstr(s1, s2, 9));
}*/