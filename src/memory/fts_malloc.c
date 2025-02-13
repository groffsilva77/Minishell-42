/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fts_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:15:00 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/12 17:44:44 by ggroff-d         ###   ########.fr       */
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
	free(new);
	return (ptr);
}

/*resumão de ft_malloc

aqui nos estamos mexendo com lista linkada
como funciona: o ft_malloc, basicamente, será utiizado para ordernar os todos os ponteiros
para que todos eles fiquem salvos na struct memory e depois seram apagados um por um

a teoria funciona assim: ptr está apontando para um bloco de memoria, precisamos salvar ele
em uma struct (a memory no caso) mas para isso precisamos "salvar" em new.

tipo : É como quando você ganha um brinquedo novo (ptr)
	Anota num papel onde guardou ele (new)
	Coloca esse papel numa pasta especial (struct memory)
	Assim você sempre sabe onde estão todos seus brinquedos!*/