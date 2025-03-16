/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/15 18:25:33 by ggroff-d         ###   ########.fr       */
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
		free(current->ptr_for_memory_block);
		free(current);
		current = next;
	}
	shell->memory = NULL;
}
