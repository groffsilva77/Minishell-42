/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:47 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/28 19:22:38 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free_all(t_shell *shell)
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
/*the resumo

É como quando sua mãe pede para devolver TODOS os brinquedos
Você vai papel por papel da sua lista
Para cada papel:

Marca o próximo papel (para não se perder)
Devolve o brinquedo
Joga fora o papel
Vai para o próximo papel marcado

No final, sua lista fica vazia!*/