/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:34:41 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/10/30 12:47:00 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static	char	*ft_putnum(char *str, int n, int *i)
{
	if (n < 0)
	{
		str[(*i)++] = '-';
		n = -n;
	}
	if (n >= 10)
		ft_putnum(str, n / 10, i);
	str[(*i)++] = (n % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		i;

	len = ft_nbrlen(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n == -2147483648)
	{
		str[i++] = '-';
		str[i++] = '2';
		n = 147483648;
	}
	ft_putnum(str, n, &i);
	str[i] = '\0';
	return (str);
}
