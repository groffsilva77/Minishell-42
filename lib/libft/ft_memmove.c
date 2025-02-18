/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:41:35 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/22 15:02:01 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char	*d;
	char	*s;

	d = (char *)dest;
	s = (char *)src;
	if (src == NULL && dest == NULL)
		return (NULL);
	if (s > d)
		ft_memcpy(d, s, count);
	else
	{
		while (count--)
			d[count] = s[count];
	}
	return (dest);
}

/*#include <stdio.h>

int	main(void)
{
	char	*d = "Gabriel";

	printf("%s\n", (char *)ft_memmove(d + 8, d, 15));
}*/
