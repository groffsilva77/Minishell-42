/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:52:28 by ggroff-d          #+#    #+#             */
/*   Updated: 2024/11/05 17:57:27 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new;
	int		new_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen((char *)s1) - 1;
	while (start <= end && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end >= start && ft_strchr(set, s1[end]) != NULL)
		end--;
	new_len = end - start + 1;
	new = (char *)malloc((new_len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	if (new_len > 0)
		ft_strlcpy(new, s1 + start, new_len + 1);
	new[new_len] = '\0';
	return (new);
}
