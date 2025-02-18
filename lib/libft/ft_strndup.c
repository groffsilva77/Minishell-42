/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:12:41 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/12 17:44:40 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	len = ft_strnlen(s, n);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, s, len);
	new_str[len] = '\0';
	free(new_str);
	return (new_str);
}
