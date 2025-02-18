/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:52:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:51:29 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*#include <stdio.h>

int	main(void)
{
	char	a = '1';
	char	b = 'A';
	char	d = '(';

	printf("%d\n", ft_isprint(a));
	printf("%d\n", ft_isprint(b));
	printf("%d\n", ft_isprint(d));
}*/
