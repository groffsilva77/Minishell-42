/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:18:53 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/17 16:06:51 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	handle_word(const char *input, int *i, int *start, t_token **tokens)
{
	while (input[*i] && !is_whitespace(input[*i])
		&& !ft_strchr("|<>", input[*i])
		&& input[*i] != '\'' && input[*i] != '\"')
		(*i)++;
	if (*i > *start)
	{
		add_token(tokens, copy_substr(input, *start, *i - *start));
		*start = *i;
	}
}

t_token	*tokenize(const char *input)
{
	t_token	*tokens;
	int		i;
	int		start;

	i = 0;
	start = 0;
	tokens = NULL;
	while (input[i])
	{
		if (is_whitespace(input[i]))
		{
			if (i > start)
				add_token(&tokens, copy_substr(input, start, i - start));
			start = ++i;
		}
		else if (input[i] == '\'' || input[i] == '\"')
		{
			if (!handle_quotes(input, &i, &tokens))
			{
				ft_putstr_fd("Error: Unmatched quotes\n", 2);
				break ;
			}
			start = i;
		}
		else if (ft_strchr("|<>", input[i]))
			hand_spc_chars(input, &i, &start, &tokens);
		else
			handle_word(input, &i, &start, &tokens);
	}
	if (i > start)
		add_token(&tokens, copy_substr(input, start, i - start));
	return (tokens);
}
