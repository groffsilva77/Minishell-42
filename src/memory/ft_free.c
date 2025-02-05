/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/01 15:48:06 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(t_shell *shell, void *ptr)
{
	t_memory	*atl;
	t_memory	*ant;

	if (!ptr)
		return ;
	ant = NULL;
	atl = shell->memory;
	while (atl)
	{
		if (atl->next_ptr == ptr)
		{	
			if (ant)
				ant->next_ptr = atl->next_ptr;
			else
				shell->memory = atl->next_ptr;
			free(ptr);
			free(atl);
			return ;
		}
		ant = atl;
		atl = atl->next_ptr;
	}
	free(ptr);
}
