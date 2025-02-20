/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:02:48 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/18 18:46:11 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(const char *input, int *i, t_token **tokens)
{
	char	quote;
	char	*sbstr;
	int		start;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		sbstr = copy_substr(input, start, *i - start);
		if (!sbstr)
			return (0);
		(*i)++;
		if (quote == '\'')
			return (process_single_quote(input, i, tokens, sbstr));
		else
			return (process_double_quote(input, i, tokens, sbstr));
	}
	return (0);
}

void	handle_redirects(const char *input, int *i, t_token **tokens)
{
	char	*sbstr;

	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, "<<");
		(*i) += 2;
	}
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, ">>");
		(*i) += 2;
	}
	else if (input[*i] == '<' || input[*i] == '>')
	{
		sbstr = copy_substr(input, *i, 1);
		if (!sbstr)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return ;
		}
		add_token(tokens, sbstr);
		free(sbstr);
		(*i)++;
	}
}

void	hand_pipe(const char *input, int *i, t_token **tokens)
{
	(void)input;
	add_token(tokens, "|");
	(*i)++;
}

void	hand_spc_chars(const char *input, int *i, int *start, t_token **tokens)
{
	char	*sbstr;

	if (*i > *start)
	{
		sbstr = copy_substr(input, *start, *i - *start);
		if (!sbstr)
		{
			ft_putstr_fd("Error: Memory allocation failed\n", 2);
			return ;
		}
		add_token(tokens, sbstr);
		free(sbstr);
	}
	if (input[*i] == '>' || input[*i] == '<')
		handle_redirects(input, i, tokens);
	else if (input[*i] == '|')
		hand_pipe(input, i, tokens);
	*start = *i;
}
