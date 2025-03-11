/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:02:48 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/11 16:43:43 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
