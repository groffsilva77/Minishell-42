/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:22:26 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/26 16:02:55 by ggroff-d         ###   ########.fr       */
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
	new_token->value = ft_strdup(value);
	if (!value)
	{
		free(new_token);
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

int	process_single_quote(t_shell *shell, const char *input, int *i,
				t_token **tokens)
{
	(void)*input;
	(void)*i;
	add_token(tokens, shell->sbstr, 1, 0);
	free(shell->sbstr);
	return (1);
}

int	process_double_quote(t_shell *shell, const char *input, int *i,
				t_token **tokens)
{
	char	*expanded;

	(void)*input;
	(void)*i;
	expanded = expand_tokens(shell, shell->sbstr, 1);
	if (!expanded)
		return (free(shell->sbstr), 0);
	add_token(tokens, expanded, 0, 1);
	free(expanded);
	free(shell->sbstr);
	shell->sbstr = NULL;
	return (1);
}
