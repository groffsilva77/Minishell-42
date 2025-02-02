/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:47 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/01 15:47:51 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(t_shell *shell)
{
	t_memory	*atl;
	t_memory	*next;

	atl = shell->memory;
	while (atl)
	{
		next = atl->next_ptr;
		free(atl->next_ptr);
		free(atl);
		atl = next;
	}
	shell->memory = NULL;
}
