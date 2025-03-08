/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:42:32 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/08 15:38:59 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finalize_token(const char *input, int *i, int *start, t_token **tokens)
{
	char	*token;

	if (*i > *start)
	{
		token = copy_substr(input, *start, *i - *start);
		if (token)
		{
			add_token(tokens, token, 0, 0);
			free(token);
		}
	}
}

int	process_quotes(t_shell *shell, const char *input, int *i, t_token **tokens)
{
	return (handle_quotes(shell, input, i, tokens));
}

void	handle_word(const char *input, int *i, int *start, t_token **tokens)
{
	char	*word;
	int		in_quotes;
	int		j;
	char	quote;

	in_quotes = 0;
	quote = 0;
	j = *i;
	while (input[j] && (!is_whitespace(input[j]) || in_quotes)
		&& (in_quotes || !ft_strchr("|<>", input[j])))
	{
		if (!in_quotes && (input[j] == '\'' || input[j] == '"'))
		{
			quote = input[j];
			in_quotes = 1;
		}
		else if (in_quotes && input[j] == quote)
			in_quotes = 0;
		j++;
	}
	if (j > *start)
	{
		if (in_quotes)
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
			*i = j;
			*start = j;
			return ;
		}
		word = copy_substr(input, *start, j - *start);
		if (!word)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return ;
		}
		add_token(tokens, word, 0, 0);
		printf("Token criado por handle_word: %s\n", word);
		free(word);
		*start = j;
	}
	*i = j;
}

void	process_special_chars(const char *input, int *i, int *start,
		t_token **tokens)
{
	if (*start < *i)
	{
		handle_word(input, start, i, tokens);
		*start = *i;
	}
	hand_spc_chars(input, i, start, tokens);
	*start = *i;
}

void	process_word(const char *input, int *i, int *start, t_token **tokens)
{
	handle_word(input, i, start, tokens);
}
