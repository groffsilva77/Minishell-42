/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:08:14 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/28 19:26:59 by ggroff-d         ###   ########.fr       */
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
    char **new_array;
    int i;
    
	(void)new_size;
    i = 0;
    if (array)
    {
        while (array[i])
            i++;
    }
    new_array = (char **)ft_malloc(shell, sizeof(char *) * (i + 2));
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
        ft_free(shell, array);
    }
    new_array[i] = fts_strdup(shell, new_value);
    new_array[i + 1] = NULL;    
    return (new_array);
}