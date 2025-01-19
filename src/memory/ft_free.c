/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:16:34 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/18 13:29:49 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_free(t_shell *shell, void *ptr)
{
	t_memory	*atl; 
	t_memory	*ant; 

	if (!ptr)
		return;
	ant = NULL;
	atl = shell->memory;
	while (atl)
		if (atl->ptr == ptr)
	if (ant)
		ant->next = atl->next;
	else 
		shell->memory = atl->next
	free(ptr);
	free(atl);
	return;
}

/*olha o resumo

Você recebe um brinquedo para devolver
Começa a procurar na sua lista de papéis
Quando acha o papel com esse brinquedo:

Arruma a lista (liga os papéis vizinhos)
Devolve o brinquedo
Joga fora o que estava papel "que estava guardando o brinquedo"

Se não achar, continua procurando até o fim da lista*/