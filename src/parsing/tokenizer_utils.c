/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:42:32 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/18 13:07:29 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_word(const char *input, int *i, int *start, t_token **tokens)
{
	int		j;
	char	*word;
	int		in_squotes;
	int		in_dquotes;

	j = *i;
	in_squotes = 0;
	in_dquotes = 0;
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
	(*i)++;
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
