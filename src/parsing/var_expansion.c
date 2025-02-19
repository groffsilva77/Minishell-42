/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:17:54 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/18 15:59:30 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tokens(const char *token, int allow_expansion)
{
	char	*expanded;
	size_t	max_len;

	if (!token)
		return (NULL);
	max_len = ft_strlen(token) * 8 + 1;
	expanded = malloc(max_len);
	if (!expanded)
		return (NULL);
	return (process_expansion(token, expanded, max_len, allow_expansion));
}
