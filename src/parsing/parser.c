/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:26:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/19 15:04:29 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*handle_pipe(t_command *commands, t_command **atl_cmd)
{
	add_command(&commands, *atl_cmd);
	*atl_cmd = NULL;
	return (commands);
}

static int	process_token(t_command **atl_cmd, t_token **tokens, t_shell *shell)
{
	if (ft_strchr("<>", (*tokens)->value[0]))
	{
		if (!(*tokens)->next)
			return (-1);
		if (!*atl_cmd)
			*atl_cmd = create_command();
		if (!*atl_cmd)
			return (-1);
		parse_redirections(*atl_cmd, tokens);
	}
	else if (handle_arg(atl_cmd, *tokens, shell) == -1)
		return (-1);
	return (0);
}

t_command	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*commands;
	t_command	*atl_cmd;

	commands = NULL;
	atl_cmd = NULL;
	while (tokens)
	{
		if (ft_strncmp(tokens->value, "|", 1) == 0)
		{
			commands = handle_pipe(commands, &atl_cmd);
			if (!commands)
				if (atl_cmd)
					return (free_commands(atl_cmd), NULL);
		}
		else if (process_token(&atl_cmd, &tokens, shell) == -1)
		{
			free_command_list(commands);
			if (atl_cmd)
				return (free_commands(atl_cmd), NULL);
		}
		tokens = tokens->next;
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
