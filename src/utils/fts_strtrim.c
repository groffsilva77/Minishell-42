/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_strtrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:22:06 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/19 19:26:57 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fts_strtrim(const char *str)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (!str)
		return (NULL);
	start = 0;
	while (str[start] && (str[start] == ' ' || str[start] == '\t'
			|| str[start] == '\n'))
			start++;
	end = ft_strlen(str);
	while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'
			|| str[end - 1] == '\n'))
			end--;
	result = malloc(end - start + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, str + start, end - start + 1);
	return (result);
}
