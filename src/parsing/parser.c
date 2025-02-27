/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:26:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/27 14:00:38 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*creat_or_get_command(t_command *atl_cmd)
{
	if (!atl_cmd)
		atl_cmd = create_command();
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
	char		**temp;
	char		*expanded_value;
	t_command	*new_cmd;

	new_cmd = NULL;

	if (!atl_cmd || !tokens || !shell)
		return (-1);
	if (tokens->in_single_quotes)
		expanded_value = ft_strdup(tokens->value);
	else
		expanded_value = expand_tokens(shell, tokens->value, 1);
	if (!expanded_value)
		return (-1);
	if (!*atl_cmd)
	{
		new_cmd = create_command();
		if (!new_cmd)
			return (free(expanded_value), -1);
			*atl_cmd = new_cmd;
	}
	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1,
			expanded_value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		free(expanded_value);
		free_commands(*atl_cmd, shell);
		*atl_cmd = NULL;
		//free((*atl_cmd)->args);
		//(*atl_cmd)->args = NULL;
		return (-1);
	}
	(*atl_cmd)->args = temp;
	//(*atl_cmd)->args[(*atl_cmd)->argument_count] = expanded_value;
	(*atl_cmd)->argument_count++;
	//(*atl_cmd)->args[(*atl_cmd)->argument_count] = NULL;
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
		{
			if (atl_cmd)
			{
				add_command(&commands, atl_cmd);
				atl_cmd = NULL;
			}
			commands = handle_pipe(commands, &atl_cmd);
		}
		else if (ft_strchr("<>", tokens->value[0]))
		{
			if (!tokens->next)
			{
				if (!atl_cmd)
					add_command(&commands, atl_cmd);
				return (commands);
			}
			if (!atl_cmd)
				atl_cmd = create_command();
			if (!atl_cmd)
			{
				free_commands(commands, shell);
				return (NULL);
			}
			parse_redirections(atl_cmd, &tokens);
		}
		else if (handle_arg(&atl_cmd, tokens, shell) == -1)
		{
			free_commands(atl_cmd, shell);
			free_commands(commands, shell);
			return (NULL);
		}
		else
		{
			if (atl_cmd)
			{
				add_command(&commands, atl_cmd);
				atl_cmd = NULL;
			}
		}
		tokens = tokens->next;
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
