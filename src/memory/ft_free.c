/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/07 18:23:42 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void ft_free(t_shell *shell, void *ptr)
{
    t_memory *current;
    t_memory *prev;

    if (!ptr || !shell || !shell->memory)
        return;

    prev = NULL;
    current = shell->memory;
    while (current)
    {
        if (current->ptr_for_memory_block == ptr)
        {
            if (prev)
                prev->next_ptr = current->next_ptr;
            else
                shell->memory = current->next_ptr;
            free(current->ptr_for_memory_block);
            free(current);
            return;
        }
        prev = current;
        current = current->next_ptr;
    }
    free(ptr);
}

