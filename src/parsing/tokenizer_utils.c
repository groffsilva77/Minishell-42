/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:42:32 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/24 12:38:42 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	add_token(t_token **tokens, const char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return ;
	}
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

int	handle_quotes(const char *input, int *i, t_token **tokens)
{
	char	quote;
	int		start;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		add_token(tokens, copy_substr(input, start, *i - start));
		(*i)++;
		return (1);
	}
	else
	{
		ft_putstr_fd("Error: Unmatched quotes\n", 2);
		return (0);
	}
}

void	hand_spc_chars(const char *input, int *i, int *start, t_token **tokens)
{
	if (*i > *start)
		add_token(tokens, copy_substr(input, *start, *i - *start));
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, ">>");
		(*i) += 2;
	}
	else if (input[*i] == '<' || input[*i] == '>')
	{
		add_token(tokens, copy_substr(input, *i, 1));
		(*i)++;
	}
	else if (input[*i] == '|')
	{
		add_token(tokens, "|");
		(*i)++;
	}
	*start = *i;
}
