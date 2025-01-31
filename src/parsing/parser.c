/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:49:08 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 18:23:59 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command	*create_commad(void)
{
	t_command *cmd;
	
	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL; 
	cmd->argument_count = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->type = CMD_SIMPLE;
	cmd->next = NULL;
	return(cmd);

}

void	parse_redirections(t_command *cmd, t_token **tokens)
{
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
		atl->next = new_cmd;
	}
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command *commands = NULL;
	t_command *atl_cmd = NULL;

	while (tokens)
	{
		if (ft_strncmp(tokens->value, "|", 1) == 0)
		{
			add_command(&commands, atl_cmd);
			atl_cmd = NULL;
		}
		else if (ft_strchr("<>", tokens->value[0]))
		{
			if (!atl_cmd)
				atl_cmd = create_commad();
			parse_redirections(atl_cmd, &tokens);
			tokens = tokens->next;
		}
		else
		{
			if (!atl_cmd) 
				atl_cmd = create_commad();
			atl_cmd->args = ft_realloc_array(
				atl_cmd->args, atl_cmd->argument_count + 1, token->value) //adiciona o novo comando (tokens->value) a listá de argumentos atl_cmd->args
			atl_cmd->argument_count++;
		}
		tokens = tokens->next; n
	}
	if (atl_cmd)
		add_command(&commands, atl_cmd);
	return (commands);
}
