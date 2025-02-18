/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:30:15 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:54:14 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!new)
		return (NULL);
	while (*src)
		new[i++] = *src++;
	new[i] = '\0';
	return (new);
}

/*
int	main(int argc, char **argv)
{
	char	*mine;
	char	*their;

	if (argc == 2)
	{
		mine = ft_strdup(argv[1]);
		their = ft_strdup(argv[1]);
		printf("%s\n%s\n", mine, their);
	}
}*/
