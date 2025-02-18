/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:29:46 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:51:22 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
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

	printf("%d\n", ft_isdigit(a));
	printf("%d\n", ft_isdigit(b));
	printf("%d\n", ft_isdigit(d));
}*/