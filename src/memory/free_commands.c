/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:42:58 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/31 18:19:58 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *commands, t_shell *shell)
{
	t_command	*current;
	t_command	*next;

	current = commands;
	while (current)
	{
		next = current->next;
		ft_free(shell, current->input_file);
		ft_free(shell, current->output_file);
		ft_free(shell, current->args);
		ft_free(shell, current);
		current = next;
	}	
}
