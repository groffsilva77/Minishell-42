/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:42:58 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/27 14:37:13 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(t_command *commands, t_shell *shell)
{
	t_command	*current;
	t_command	*next;
	int			i;

	current = commands;
	while (current)
	{
		next = current->next;
		ft_free(shell, current->input_file);
		current->input_file = NULL;
		ft_free(shell, current->output_file);
		current->output_file = NULL;
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				ft_free(shell, current->args[i]);
				current->args[i] = NULL;
				i++;
			}
			ft_free(shell, current->args);
			current->args = NULL ;
		}
		ft_free(shell, current);
		current = next;
	}
}

/* {
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
} */
