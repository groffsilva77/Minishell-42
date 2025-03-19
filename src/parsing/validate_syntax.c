/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:00 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 15:00:30 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_operator(const char *token)
{
	return (!ft_strcmp(token, "|") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<<") || !ft_strcmp(token, "<>"));
}

static int	print_syntax_error(t_shell *shell, const char *message,
				const char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd((char *)token, 2);
	else
		ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 2;
	return (0);
}

int	validate_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	if (!tokens)
	{
		shell->exit_status = 2;
		return (0);
	}
	current = tokens;
	if (!ft_strcmp(current->value, "|"))
		return (print_syntax_error(shell, NULL, "|"));
	while (current->next)
	{
		if (is_operator(current->value))
		{
			if (is_operator(current->next->value))
				return (print_syntax_error(shell, NULL, current->next->value));
		}
		current = current->next;
	}
	if (is_operator(current->value))
		return (print_syntax_error(shell, "newline", NULL));
	return (1);
}
