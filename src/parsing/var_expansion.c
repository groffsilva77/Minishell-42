/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:17:54 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/25 12:57:19 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tokens(t_shell *shell, const char *token, int allow_expansion)
{
	size_t	max_len;
	char	*result;

	if (!shell || !token || !shell->env_copy || !shell->expand)
		return (NULL);
	max_len = ft_strlen(token) * 8 + 1;
	if (max_len > 4096)
		return (NULL);
	ft_memset(shell->expand, 0, 4096);
	result = process_expansion(shell, token, max_len, allow_expansion);
	if (!result)
		return (NULL);
	return (ft_strdup(result));
}
