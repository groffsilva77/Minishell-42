/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:32:45 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:51:13 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
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

	printf("%d\n", ft_isascii(a));
	printf("%d\n", ft_isascii(b));
	printf("%d\n", ft_isascii(d));
}*/
