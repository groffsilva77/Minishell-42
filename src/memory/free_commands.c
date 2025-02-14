/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:42:58 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/14 18:28:35 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *commands, t_shell *shell)
{
	t_command	*current;
	t_command	*next;

	next = NULL;
	current = commands;
	while (current)
	{
		// next = current->next;
		ft_free(shell, current->input_file);
		ft_free(shell, current->output_file);
		ft_free(shell, current->args);
		ft_free(shell, current);
		current = next;
	}	
}
