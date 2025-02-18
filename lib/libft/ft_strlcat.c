/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:26:12 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:56:00 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	i = 0;
	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	while (src[i] && ((--size - dest_len) > 0) && ++i)
		dest[dest_len + i - 1] = src[i - 1];
	dest[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
/*#include <stdio.h>

int	main(void)
{
	char	*src = " World!";
	char	*dest = "Hello,";

	printf("%zu\n", ft_strlcat(dest, src, 15));
}*/