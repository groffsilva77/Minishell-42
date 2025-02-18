/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:53:33 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:50:41 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
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

	printf("%d\n", ft_isalpha(a));
	printf("%d\n", ft_isalpha(b));
	printf("%d\n", ft_isalpha(d));
}*/
