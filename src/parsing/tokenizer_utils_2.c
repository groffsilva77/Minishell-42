/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:02:48 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/08 15:38:53 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(t_shell *shell, const char *input, int *i, t_token **tokens)
{
	char	quote;
	int		start;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] == quote)
	{
		shell->sbstr = copy_substr(input, start, *i - start);
		if (!shell->sbstr)
			return (0);
		(*i)++;
		printf("handle_quotes: quote=%c, sbstr=%s\n", quote, shell->sbstr);
		if (quote == '"')
			return (process_double_quote(shell, input, i, tokens));
		else if (quote == '\'')
			return (process_single_quote(shell, input, i, tokens));
		return (0);
	}
	return (0);
}

void	handle_redirects(const char *input, int *i, t_token **tokens)
{
	char	*sbstr;

	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		add_token(tokens, "<<", 0, 0);
		(*i) += 2;
	}
	if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, ">>", 0, 0);
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
		add_token(tokens, sbstr, 0, 0);
		free(sbstr);
		(*i)++;
	}
}

void	hand_pipe(const char *input, int *i, t_token **tokens)
{
	(void)input;
	add_token(tokens, "|", 0, 0);
	(*i)++;
}

void	hand_spc_chars(const char *input, int *i, int *start, t_token **tokens)
{
	(void)start;
	if (input[*i] == '<' && input[*i + 1] == '<')
	{	
		add_token(tokens, "<<", 0, 0);
		*i += 2;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		add_token(tokens, ">>", 0, 0);
		*i += 2;
	}
	else if (input[*i] == '<' || input[*i] == '>' || input[*i] == '|')
	{
		add_token(tokens, ft_substr(input, *i, 1), 0, 0);
		(*i)++;
	}	
}
