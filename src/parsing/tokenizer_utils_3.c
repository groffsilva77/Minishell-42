/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:22:26 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/18 13:06:14 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **tokens, const char *value, int in_squotes,
					int in_dquotes)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	if (!value)
		new_token->value = ft_strdup("");
	else
	{
		new_token->value = ft_strdup(value);
		if (!new_token->value)
			return ;
	}
	new_token->in_single_quotes = in_squotes;
	new_token->in_double_quotes = in_dquotes;
	new_token->next = NULL;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

char	*copy_substr(const char *input, int start, int length)
{
	char	*substr;

	if (length < 0)
		return (NULL);
	substr = malloc(length + 1);
	if (!substr)
		return (NULL);
	ft_strncpy(substr, input + start, length);
	substr[length] = '\0';
	return (substr);
}
