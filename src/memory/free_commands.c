/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:42:58 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/17 16:38:18 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void free_commands(t_command *commands)
{

    if (commands)
    {/* 
        if (commands->args)
        {
            i = -1;
            while (commands->args[++i])
                free(commands->args[i]);
            free(commands->args);
        }
        if (commands->heredoc_delims)
        {
            i = -1;
            while (commands->heredoc_delims[++i])
                free(commands->heredoc_delims[i]);
            free(commands->heredoc_delims);
        }
        if (commands->heredoc_pipe[0] != -1)
            close(commands->heredoc_pipe[0]);
        if (commands->heredoc_pipe[1] != -1)
            close(commands->heredoc_pipe[1]);
        free(commands->input_file);
        free(commands->output_file);
        free(commands->heredoc_delim); */
        free(commands);
    }
}


void	free_command_list(t_command *cmd_list)
{
	t_command	*current;
	t_command	*next;

	//cmd_list = NULL;
	current = cmd_list;
	while (current)
	{
		next = current->next;
		free_commands(current);
		current = next;
	}
}