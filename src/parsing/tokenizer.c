/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:18:53 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/26 15:57:44 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_whitespace(const char *input, int *i, int *start,
		t_token **tokens)
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
	*start = ++(*i);
}

t_token	*tokenize(t_shell *shell, const char *input)
{
	t_token	*tokens;
	int		i;
	int		start;

	tokens = NULL;
	i = 0;
	start = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			process_whitespace(input, &i, &start, &tokens);
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (!process_quotes(shell, input, &i, &tokens))
				break ;
			start = i;
		}
		else if (ft_strchr("|<>", input[i]))
			process_special_chars(input, &i, &start, &tokens);
		else
			process_word(input, &i, &start, &tokens);
	}
	finzalize_token(input, &i, &start, &tokens);
	return (tokens);
}
