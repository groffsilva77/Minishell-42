/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/17 16:12:59 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_shell *shell)
{
	t_memory	*current;
	t_memory	*next;

	if (!shell)
		return ;
	current = shell->memory;
	while (current)
	{
		next = current->next_ptr;
		if (current->ptr_for_memory_block)
			free(current->ptr_for_memory_block);
		free(current);
		current = next;
	}
	shell->memory = NULL;
}
