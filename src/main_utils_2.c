/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:58:40 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/04 16:53:25 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
		return ;
	if (shell->expand)
		free(shell->expand);
	if (shell->sbstr)
		free(shell->sbstr);
	if (shell->env_copy)
	{
		while (shell->env_copy[i])
			free(shell->env_copy[i++]);
		free(shell->env_copy);
	}
	if (shell->memory)
		free(shell->memory);
	free(shell);
}

char	**duplicate_env(char **env)
{
	int		i;
	char	**copy;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			return (free(copy), NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->expand = malloc(4096);
	shell->sbstr = malloc(4096);
	if (!shell->expand || !shell->sbstr)
	{
		free(shell->expand);
		free(shell->sbstr);
		free(shell);
		return (NULL);
	}
	shell->memory = NULL;
	shell->env_copy = duplicate_env(env);
	if (!shell->env_copy)
	{
		free(shell->expand);
		free(shell->sbstr);
		free(shell);
		return (NULL);
	}
	shell->exit_status = 0;
	return (shell);
}
