/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:06:21 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/14 18:15:59 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->argument_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->type = CMD_SIMPLE;
	cmd->next = NULL;
	free(cmd);
	return (cmd);
}

void	parse_redirections(t_command *cmd, t_token **tokens)
{
	if (!(*tokens) || !(*tokens)->next)
		return ;
	if (ft_strncmp((*tokens)->value, "<", 1) == 0)
		cmd->input_file = ft_strdup((*tokens)->next->value);
	else if (ft_strncmp((*tokens)->value, ">", 1) == 0)
		cmd->output_file = ft_strdup((*tokens)->next->value);
	else if (ft_strncmp((*tokens)->value, ">>", 2) == 0)
		cmd->output_file = ft_strdup((*tokens)->next->value);
	*tokens = (*tokens)->next;
}

void	add_command(t_command **commands, t_command *new_cmd)
{
	t_command	*atl;

	if (!*commands)
		*commands = new_cmd;
	else
	{
		atl = *commands;
		while (atl->next)
			atl = atl->next;
		atl->next = new_cmd;
	}
}
