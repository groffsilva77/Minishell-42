/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 09:27:53 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/17 15:43:26 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	value;
	size_t			i;

	i = 0;
	ptr = str;
	value = (unsigned char)c;
	while (i < n)
	{
		ptr[i] = value;
		i++;
	}
	return (str);
}
