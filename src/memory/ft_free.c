/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/27 13:39:37 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	ft_free(t_shell *shell, void *ptr)
{
	t_memory	*atl;
	t_memory	*ant;

	if (!ptr)
		return ;
	ant = NULL;
	atl = shell->memory;
	printf("ft_free: Liberando %p\n", ptr);
	while (atl)
	{
		if (atl->ptr_for_memory_block == ptr)
		{
			if (ant)
				ant->next_ptr = atl->next_ptr;
			else
				shell->memory = atl->next_ptr;
			free(atl->ptr_for_memory_block);
			free(atl);
			return ;
		}
		ant = atl;
		atl = atl->next_ptr;
	}
	free(ptr);
}

/* {
	t_memory	*atl;
	t_memory	*ant;

	if (!ptr)
		return ;
	ant = NULL;
	atl = shell->memory;
	while (atl)
	{	
		if (ant)
			ant->next_ptr = atl->next_ptr;
		return ;
		ant = atl;
		atl = atl->next_ptr;
	}
	free(ptr);
} */
