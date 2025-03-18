/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:15:22 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/18 14:01:54 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc_array(char **array, int new_size, char *new_value,
			t_shell *shell)
{
	char	**new_array;
	int		i;

	if (new_size <= 0)
		return (NULL);
	new_array = (char **)fts_malloc(shell, sizeof(char *) * (new_size + 1));
	if (!new_array)
		return (NULL);
	i = 0;
	while (array && array[i] && i < new_size)
	{
		new_array[i] = array[i];
		i++;
	}
	if (new_value)
	{
		new_array[i] = fts_strdup(shell, new_value);
		if (!new_array[i])
		{
			return (free(new_array), NULL);
		}
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
