/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:15:00 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/07 20:11:25 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*fts_malloc(t_shell *shell, size_t size)
{
	t_memory	*new;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new = malloc(sizeof(t_memory));
	if (!new)
	{
		free(ptr);
		return (NULL);
	}
	new->ptr_for_memory_block = ptr;
	new->next_ptr = shell->memory;
	shell->memory = new;
	//free(new);
	return (ptr);
}
