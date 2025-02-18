/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:27:18 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/06 09:54:22 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	total_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = (char *)malloc(total_len * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, s1, total_len - ft_strlen(s2));
	ft_strlcat(new, s2, total_len);
	return (new);
}
