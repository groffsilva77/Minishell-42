/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:47 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/20 18:21:51 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_shell *shell)
{
	t_memory	*current;
	t_memory	*next;

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
