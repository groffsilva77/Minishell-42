/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 19:23:16 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:24:10 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*al_memory;
	size_t	nsize;

	if (num != 0 && size != 0 && num > (size_t) - 1 / size)
		return (NULL);
	nsize = num * size;
	al_memory = malloc(nsize);
	if (!al_memory)
		return (NULL);
	ft_memset(al_memory, 0, nsize);
	return (al_memory);
}
