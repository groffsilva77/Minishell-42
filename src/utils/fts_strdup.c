/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_strdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:31:21 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/02 16:16:26 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strdup(t_shell *shell, const char *s1)
{
	char	*dup;
	size_t	len;

	len = strlen(s1);
	dup = ft_malloc(shell, len + 1);
	if (!dup)
		return (NULL);
	memcpy(dup, s1, len + 1);
	return (dup);
}
