/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:08:14 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 18:58:32 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
A função ft_realloc_array serve para:

Realocar memória para o array, aumentando seu tamanho para acomodar novos elementos.
Preservar os valores existentes no array original.
Adicionar o novo elemento ao final do array.

real objetivo: ela é essencial para gerenciar o crescimento dinâmico do array de argumentos (args) dentro de t_command

A ideia aqui é criar um novo espaço na memória que seja maior que o antigo, para comportar um novo elemento, além de copiar os valores existentes do array original.
*/

#include "minishell.h"

char	**realloc_array(char **array, int n_size, char *n_value, t_shell *shell)
{
	char	**new_array;
	int		i;

	new_array = (char **)ft_malloc(shell, sizeof(char *) *(new_array + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	if (array)
	{
		while (array[i])
		{
			new_array[i] = array[i];
			i++;
		}
		ft_free(shell, array)
	}
		new_array[i] = fts_strdup(n_value);
		new_array[i + 1] = NULL;
		return (new_array);
}
