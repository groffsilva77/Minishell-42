/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:42:32 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 15:07:43 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calculate_word_length(const char *input, int start)
{
	int	j;
	int	in_squotes;
	int	in_dquotes;

	in_squotes = 0;
	in_dquotes = 0;
	j = start;
	while (input[j])
	{
		if (input[j] == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		else if (input[j] == '\"' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (!in_squotes && !in_dquotes && is_whitespace(input[j]))
			break ;
		j++;
	}
	return (j);
}

void	handle_word(const char *input, int *i, int *start, t_token **tokens)
{
	int		j;
	char	*word;

	(*i)++;
	j = calculate_word_length(input, *start);
	if (j > *start)
	{
		word = copy_substr(input, *start, j - *start);
		if (!word)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return ;
		}
		if (*tokens == NULL || ft_strcmp((*tokens)->value, word) != 0)
			add_token(tokens, word, 0, 0);
		free(word);
	}
	*i = j;
	*start = j;
}

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

void	process_word(t_shell *shell, t_word_data *data)
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
