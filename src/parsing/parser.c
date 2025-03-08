/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:26:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/08 18:05:54 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_or_get_command(t_command *atl_cmd, t_shell *shell)
{
	if (!atl_cmd)
		atl_cmd = create_command(shell);
	return (atl_cmd);
}

t_command	*handle_pipe(t_command *commands, t_command **atl_cmd)
{
	add_command(&commands, *atl_cmd);
	*atl_cmd = NULL;
	return (commands);
}

int	handle_arg(t_command **atl_cmd, t_token *tokens, t_shell *shell)
{
	char	**temp;
	char	*expanded_value;

	if (tokens->in_single_quotes)
		expanded_value = ft_strdup(tokens->value);
	else
		expanded_value = expand_tokens(shell, tokens->value, 1);
	if (!expanded_value)
		return (-1);
	*atl_cmd = create_or_get_command(*atl_cmd, shell);
	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1,
			expanded_value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		free(expanded_value);
		return (-1);
	}
	(*atl_cmd)->args = temp;
	(*atl_cmd)->argument_count++;
	free(expanded_value);
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
			commands = handle_pipe(commands, &atl_cmd);
		else if (ft_strchr("<>", tokens->value[0]))
		{
			if (!tokens->next)
				return (commands);
			if (!atl_cmd)
				atl_cmd = create_command(shell);
			parse_redirections(atl_cmd, &tokens, shell);
		}
		else if (handle_arg(&atl_cmd, tokens, shell) == -1)
		{
			if (atl_cmd)
				free_commands(atl_cmd, shell);
			free_commands(commands, shell);
			return (NULL);
		}
		tokens = tokens->next;
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
