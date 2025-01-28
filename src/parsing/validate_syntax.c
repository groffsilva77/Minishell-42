/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:26:00 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/28 15:32:54 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_operator(const char *token)
{
	return (!ft_strcmp(token, "|") || !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<<"));
}

int	validate_syntax(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	if (!tokens)
		return (write(2, "Error: Empty command.\n", 22), 0);
	current = tokens;
	if (is_operator(current->value))
		return (write(2,
				"Error: Command cannot start with an operator.\n", 46), 0);
	while (current)
	{
		next = current->next;
		if (is_operator(current->value))
		{
			if (!next)
				return (write(2,
						"Error: Command cannot end with an operator.\n", 44), 0);
			if (is_operator(next->value))
				return (write
					(2, "Error: Consecutive operators are not allowed.\n", 47),
					0);
		}
		current = current->next;
	}
	return (1);
}
