/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:15:00 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/20 18:24:08 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*fts_malloc(t_shell *shell, size_t size)
{
	t_memory	*new;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("malloc failed for ptr\n", 2);
		return (NULL);
	}
	new = malloc(sizeof(t_memory));
	if (!new)
	{
		ft_putstr_fd("malloc failed for t_memory\n", 2);
		free(ptr);
		return (NULL);
	}
	new->ptr_for_memory_block = ptr;
	new->next_ptr = shell->memory;
	shell->memory = new;
	return (ptr);
}
