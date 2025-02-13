/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:42:32 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/05 16:17:39 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finzalize_token(const char *input, int *i, int *start, t_token **tokens)
{
	char	*token;

	if (*i > *start)
	{
		token = copy_substr(input, *start, *i - *start);
		if (token)
		{
			add_token(tokens, token);
			free(token);
		}
	}
}

int	process_quotes(const char *input, int *i, t_token **tokens)
{
	if (!&handle_quotes)
		ft_putstr_fd("Error: Unmatched quotes\n", 2);
	return (handle_quotes(input, i, tokens));
}

void	process_special_chars(const char *input, int *i, int *start,
		t_token **tokens)
{
	hand_spc_chars(input, i, start, tokens);
}

void	handle_word(const char *input, int *i, int *start, t_token **tokens)
{
	char	*word;

	while (input[*i] && !is_whitespace(input[*i])
		&& !ft_strchr("|<>", input[*i])
		&& input[*i] != '\'' && input[*i] != '\"')
		(*i)++;
	if (*i > *start)
	{
		word = copy_substr(input, *start, *i - *start);
		if (!word)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return ;
		}
		add_token(tokens, word);
		free(word);
		*start = *i;
	}
}

void	process_word(const char *input, int *i, int *start, t_token **tokens)
{
	handle_word(input, i, start, tokens);
}
