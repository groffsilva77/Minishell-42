/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:15:22 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/21 17:05:43 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc_array(char **array, int new_size, char *new_value,
			t_shell *shell)
{
	char	**new_array;
	int		i;

	if (new_size <= 0 || !new_value)
		return (NULL);
	new_array = (char **)fts_malloc(shell, sizeof(char *) * (new_size + 1));
	if (!new_array)
		return (ft_putstr_fd("fts_malloc failed\n", 2), NULL);
	i = 0;
	while (array && array[i] && i < new_size - 1)
	{	
		new_array[i] = array[i];
		i++;
	}
	new_array[i] = fts_strdup(shell, new_value);
	if (!new_array[i])
	{
		ft_putstr_fd("fts_strdup failed\n", 2);
		while (i > 0)
			ft_free(shell, new_array[--i]);
		return (ft_free(shell, new_array), NULL);
	}
	new_array[new_size] = NULL;
	if (array)
		ft_free(shell, array);
	return (new_array);
}
