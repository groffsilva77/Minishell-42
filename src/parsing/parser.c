/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:49:08 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/21 17:03:02 by ggroff-d         ###   ########.fr       */
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
	char	**temp;

	if (!tokens || !tokens->value)
		return (ft_putstr_fd("Error: tokens or tokens->value is NULL\n", 2), -1);
	ft_putstr_fd("tokens->value: ", 2);
	ft_putendl_fd(tokens->value, 2);
	*atl_cmd = creat_or_get_command(*atl_cmd);
	if (!*atl_cmd)
		return (ft_putstr_fd("Error: creat_or_get_command failed\n", 2), -1);
	ft_putstr_fd("argument_count: ", 2);
	ft_putnbr_fd((*atl_cmd)->argument_count, 2);
	ft_putstr_fd("\n", 2);
	temp = ft_realloc_array((*atl_cmd)->args, (*atl_cmd)->argument_count + 1,
			tokens->value, shell);
	if (!temp)
	{
		ft_putstr_fd("Error: Memory allocation failed in realloc array\n", 2);
		ft_free_array((*atl_cmd)->args);
		return ((*atl_cmd)->args = NULL, -1);
	}
	(*atl_cmd)->args = temp;
	(*atl_cmd)->argument_count++;
	return (0);
}

t_command	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_command	*commands;
	t_command	*atl_cmd;
	char		*expanded;

	commands = NULL;
	atl_cmd = NULL;
	while (tokens)
	{
		ft_putstr_fd("Parsing token: ", 2);
		ft_putendl_fd(tokens->value, 2);
		if (ft_strncmp(tokens->value, "|", 1) == 0)
			commands = handle_pipe(commands, &atl_cmd);
		else if (ft_strchr("<>", tokens->value[0]))
		{
			if (!tokens->next)
				return (commands);
			if (!atl_cmd)
				atl_cmd = create_command();
			parse_redirections(atl_cmd, &tokens);
		}
		else
		{
			if (!atl_cmd)
				atl_cmd = create_command();
			expanded = expand_tokens(tokens->value, !tokens->is_single_quoted);
			if (!expanded)
				return (NULL);
			ft_putstr_fd("Expanded to: ", 2);
			ft_putendl_fd(expanded, 2);
			free(tokens->value);
			tokens->value = expanded;
			if (handle_arg(&atl_cmd, tokens, shell) == -1)
				return (NULL);
		}
		tokens = tokens->next;
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
