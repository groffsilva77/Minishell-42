/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:42:58 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/07 17:38:08 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_commands(t_command *commands, t_shell *shell)
{
    t_command *current;
    t_command *next;
    int i;

    current = commands;
    while (current)
    {
        next = current->next;
        ft_free(shell, current->input_file);
        ft_free(shell, current->output_file);
        ft_free(shell, current->heredoc_delim);
        if (current->args)
        {
            i = 0;
            while (current->args[i])
            {
                ft_free(shell, current->args[i]);
                i++;
            }
            ft_free(shell, current->args);
        }
        ft_free(shell, current);
        current = next;
    }
}