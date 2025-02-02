/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:15:22 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/02 16:15:37 by ggroff-d         ###   ########.fr       */
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
