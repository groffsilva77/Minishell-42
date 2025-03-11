/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:00 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/11 17:03:49 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(const char *token)
{
	return (!ft_strcmp(token, "|") || !ft_strcmp(token, ">")
		|| !ft_strcmp(token, "<") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<<"));
}

int	validate_syntax(t_token *tokens, t_shell *shell)
{
	t_token	*current;

	if (!tokens)
		return (1);
	current = tokens;
	if (!ft_strcmp(current->value, "|"))
		return (ft_putstr_fd(
				"minishell: syntax error near unexpected token `|'\n", 2),
			shell->exit_status);
	while (current->next)
	{
		if (is_operator(current->value))
		{
			if (is_operator(current->next->value))
				return (ft_putstr_fd("minishell: syntax error near unexpected token `\n", 2),
					write(2, current->next->value,
						ft_strlen(current->next->value)),
					ft_putstr_fd("'\n", 2), shell->exit_status);
		}
		current = current->next;
	}
	if (is_operator(current->value))
		return (ft_putstr_fd( "minishell: syntax error near unexpected token `newline'\n", 2),
			shell->exit_status);
	return (1);
}
