/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:00:41 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:19 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_delim(t_command *cmd, char *delim_value)
{
	t_delim	*new_delim;
	t_delim	*current;

	new_delim = malloc(sizeof(t_delim));
	if (!new_delim)
		return ;
	new_delim->value = ft_strdup(delim_value);
	new_delim->next = NULL;
	if (!cmd->delim_list)
		cmd->delim_list = new_delim;
	else
	{
		current = cmd->delim_list;
		while (current->next)
			current = current->next;
		current->next = new_delim;
	}
	if (cmd->heredoc_delim)
		free(cmd->heredoc_delim);
	cmd->heredoc_delim = ft_strdup(delim_value);
	cmd->is_heredoc = 1;
}
