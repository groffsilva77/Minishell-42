/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:44:24 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/14 17:37:55 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

//#include <stdio.h>
/*int	main(void)
{
	char	buff[50];

	ft_bzero(buff, 10);
	buff[10] = '\0';
	printf("%s\n", buff);
}*/
