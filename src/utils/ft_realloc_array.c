/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:08:14 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/02 15:42:47 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc_array(char **array, int new_size, char *new_value,
			t_shell *shell)
{
	char	**new_array;
	int		i;

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
	return (new_array[i + 1] = NULL, new_array);
}
