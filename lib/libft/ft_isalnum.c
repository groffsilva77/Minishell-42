/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:42 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:50:25 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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

	printf("%d\n", ft_isalnum(a));
	printf("%d\n", ft_isalnum(b));
	printf("%d\n", ft_isalnum(d));
}*/
