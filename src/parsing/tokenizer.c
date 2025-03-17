/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:18:53 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/16 19:27:54 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quotes(char *word, int len, int *has_squotes, int *has_dquotes)
{
	int	i;

	i = -1;
	*has_squotes = 0;
	*has_dquotes = 0;
	while (++i < len)
	{
		if (word[i] == '\'')
			*has_squotes = 1;
		else if (word[i] == '"')
			*has_dquotes = 1;
	}
}

void	process_word(t_shell *shell, t_word_d *data)
{
	char	*word;
	int		has_squotes;
	int		has_dquotes;

	(void)shell;
	word = copy_substr(data->input, data->start, data->len);
	if (!word)
		return ;
	process_quotes(word, data->len, &has_squotes, &has_dquotes);
	if (has_squotes)
		add_token(data->tokens, word, 1, 0);
	else if (has_dquotes)
		add_token(data->tokens, word, 0, 1);
	else
		add_token(data->tokens, word, 0, 0);
	free(word);
}

void	handle_special_char(const char *input, int i, t_token **tokens)
{
	char	*special;

	if ((input[i] == '<' && input[i + 1] == '<')
		|| (input[i] == '>' && input[i + 1] == '>'))
	{
		special = copy_substr(input, i, 2);
		add_token(tokens, special, 0, 0);
		free(special);
		i++;
	}
	else
	{
		special = copy_substr(input, i, 1);
		add_token(tokens, special, 0, 0);
		free(special);
	}
}

void	process_current_char(t_shell *shell, const char *input,
		t_tokenize_data *data, t_token **tokens)
{
	t_word_d	word_data;

	if (!is_whitespace(input[data->i]) && !ft_strchr("|<>", input[data->i]))
	{
		if (!data->in_word)
		{
			data->word_start = data->i;
			data->in_word = 1;
		}
	}
	else if (ft_strchr("|<>", input[data->i]))
	{
		if (data->in_word)
		{
			word_data = (t_word_d){input, data->word_start,
				data->i - data->word_start, tokens};
			process_word(shell, &word_data);
			data->in_word = 0;
		}
		handle_special_char(input, data->i, tokens);
		data->i++;
	}
	else if (is_whitespace(input[data->i]) && data->in_word)
	{
		word_data = (t_word_d){input, data->word_start,
			data->i - data->word_start, tokens};
		process_word(shell, &word_data);
		data->in_word = 0;
	}
}

t_token	*tokenize(t_shell *shell, const char *input)
{
	t_token			*tokens;
	t_tokenize_data	data;
	t_word_d		word_data;

	tokens = NULL;
	data.i = 0;
	data.word_start = 0;
	data.in_word = 0;
	while (input[data.i])
	{
		process_current_char(shell, input, &data, &tokens);
		data.i++;
	}
	if (data.in_word)
	{
		word_data = (t_word_d){input, data.word_start,
			data.i - data.word_start, &tokens};
		process_word(shell, &word_data);
	}
	return (tokens);
}
