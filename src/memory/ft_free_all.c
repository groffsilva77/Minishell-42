/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:47 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/26 17:21:12 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_shell *shell)
{
	t_memory	*atl;
	t_memory	*next;
	int			i;

	atl = shell->memory;
	while (atl)
	{
		next = atl->next_ptr;
		free(atl->ptr_for_memory_block);
		free(atl);
		atl = next;
	}
	shell->memory = NULL;
	free(shell->expand);
	free(shell->sbstr);
	if (shell->env_copy)
	{
        i = 0;
		while (shell->env_copy[i])
			free(shell->env_copy[i++]);
		free(shell->env_copy);
	}
	free(shell);
}

/* {
	t_memory	*atl;
	t_memory	*next;

	atl = shell->memory;
	while (atl)
	{
		next = atl->next_ptr;
		free(atl->ptr_for_memory_block);
		free(atl);
		atl = next;
	}
	shell->memory = NULL;
} */
