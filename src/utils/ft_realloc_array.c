/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:08:14 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/23 16:35:16 by ytavares         ###   ########.fr       */
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

char **ft_realloc_array(char **array, int new_size, char *new_value, t_shell *shell)
{
	char **new_array; //nova array
	int i;
	
	new_array = (char **)ft_malloc(shell, sizeof(char *) *(new_array + 1));
	if (!new_array) //aloca espaço para o nova array
		return (NULL);
	i = 0;
	if (array)
	{
		while (array[i])
		{
			new_array[i] = array[i];  //copia os elementos da array original para nova array
			i++;
		}
		ft_free(shell, array) // libera o array original
	}
	new_array[i] = ft_strdup(new_value);  //a nova array recebe o novo valor
	new_array[i + 1] = NULL; //define o último elemento como NULL
	return (new_array);
}