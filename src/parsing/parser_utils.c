/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:06:21 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 15:01:46 by ggroff-d         ###   ########.fr       */
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
	cmd->is_heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->heredoc_delim = NULL;
	cmd->type = CMD_SIMPLE;
	cmd->next = NULL;
	cmd->append_output = 0;
	cmd->is_builtin = 0;
	cmd->heredoc_pipe[0] = -1;
	cmd->heredoc_pipe[1] = -1;
	cmd->input_fd = -1;
	cmd->output_fd = -1;
	return (cmd);
}

static void	handle_the_heredoc(t_command *cmd, t_token **tokens)
{
	if (ft_strchr("<>", (*tokens)->next->value[0]))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			(*tokens)->next->value);
		*tokens = NULL;
		return ;
	}
	free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup((*tokens)->next->value);
	cmd->is_heredoc = 1;
}

void	parse_redirections(t_command *cmd, t_token **tokens)
{
	if (!tokens || !(*tokens) || !(*tokens)->next)
		return ;
	if (ft_strncmp((*tokens)->value, "<<", 2) == 0)
		handle_the_heredoc(cmd, tokens);
	else if (ft_strncmp((*tokens)->value, "<", 1) == 0)
	{
		free(cmd->input_file);
		cmd->input_file = ft_strdup((*tokens)->next->value);
		cmd->type = CMD_REDIR_IN;
	}
	else if (ft_strncmp((*tokens)->value, ">>", 2) == 0)
	{
		free(cmd->output_file);
		cmd->output_file = ft_strdup((*tokens)->next->value);
		cmd->append_output = 1;
	}
	else if (ft_strncmp((*tokens)->value, ">", 1) == 0)
	{
		free(cmd->output_file);
		cmd->output_file = ft_strdup((*tokens)->next->value);
	}	
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

t_command	*create_or_get_command(t_command *atl_cmd)
{
	if (!atl_cmd)
		atl_cmd = create_command();
	return (atl_cmd);
}
