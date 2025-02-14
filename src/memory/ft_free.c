/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/14 18:27:33 by ggroff-d         ###   ########.fr       */
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
		if (ant)
			ant->next_ptr = atl->next_ptr;
		return ;
		ant = atl;
		atl = atl->next_ptr;
	}
	free(ptr);
}
