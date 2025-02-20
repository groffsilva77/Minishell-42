/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:17:54 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/20 13:19:23 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_tokens(t_shell *shell, const char *token, int allow_expansion)
{
	char	*expanded;
	size_t	max_len;

	if (!token)
	{
		printf("expand_tokens: Erro! token é NULL\n");
		return (NULL);
	}
	printf("expand_tokens: Antes da expansão, token '%s'\n", token);
	max_len = ft_strlen(token) * 8 + 1;
	expanded = malloc(max_len);
	if (!expanded)
	{
		printf("expand_tokens: Erro! Falha ao alocar memória para expanded\n");
		return (NULL);
	}
	return (process_expansion(shell, token, expanded, max_len, allow_expansion));
}
