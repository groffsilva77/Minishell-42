/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:18:53 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 17:08:40 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_word_characters(t_shell *shell, const char *input,
					t_tokenize_data *data, t_token **tokens)
{
	(void)shell;
	(void)tokens;
	if (input[data->i] == '\'' || input[data->i] == '"')
	{
		if (!data->quote)
		{
			data->quote = input[data->i];
			if (!data->in_word)
			{
				data->word_start = data->i;
				data->in_word = 1;
			}
		}
		else if (data->quote == input[data->i])
			data->quote = 0;
	}
	else if (!data->quote && !is_whitespace(input[data->i])
		&& !ft_strchr("|<>", input[data->i]))
	{
		if (!data->in_word)
		{
			data->word_start = data->i;
			data->in_word = 1;
		}
	}
}

static void	handle_special_and_whitespace(t_shell *shell, const char *input,
	t_tokenize_data *data, t_token **tokens)
{
	t_word_data	word_data;

	if (!data->quote && ft_strchr("|<>", input[data->i]))
	{
		if (data->in_word)
		{
			word_data = (t_word_data){input, data->word_start,
				data->i - data->word_start, tokens};
			process_word(shell, &word_data);
			data->in_word = 0;
		}
		handle_special_char(input, data->i, tokens);
		data->i++;
	}
	else if (!data->quote && is_whitespace(input[data->i]) && data->in_word)
	{
		word_data = (t_word_data){input, data->word_start,
			data->i - data->word_start, tokens};
		process_word(shell, &word_data);
		data->in_word = 0;
	}
}

void	process_current_char(t_shell *shell, const char *input,
	t_tokenize_data *data, t_token **tokens)
{
	handle_word_characters(shell, input, data, tokens);
	handle_special_and_whitespace(shell, input, data, tokens);
}

static void	init_tokenize_data(t_tokenize_data *data, t_token **tokens)
{
	*tokens = NULL;
	data->i = 0;
	data->word_start = 0;
	data->in_word = 0;
	data->quote = 0;
}

t_token	*tokenize(t_shell *shell, const char *input)
{
	t_token			*tokens;
	t_tokenize_data	data;
	t_word_data		word_data;

	init_tokenize_data(&data, &tokens);
	while (input[data.i])
	{
		process_current_char(shell, input, &data, &tokens);
		if (input[data.i])
			data.i++;
	}
	if (data.in_word)
	{
		word_data = (t_word_data){input, data.word_start,
			data.i - data.word_start, &tokens};
		process_word(shell, &word_data);
	}
	if (data.quote)
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			2);
		ft_putchar_fd(data.quote, 2);
		return (ft_putstr_fd("'\n", 2), free_token_list(tokens), NULL);
	}
	return (tokens);
}
