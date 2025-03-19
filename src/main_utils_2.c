/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:58:40 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/19 11:33:00 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(char **env_copy)
{
	int	i;

	if (!env_copy)
		return ;
	i = 0;
	while (env_copy[i])
		free(env_copy[i++]);
	free(env_copy);
}

void	free_shell(t_shell *shell)
{
	t_memory	*current;
	t_memory	*next;

	if (!shell)
		return ;
	free(shell->expand);
	free(shell->sbstr);
	if (shell->env_copy)
		free_env(shell->env_copy);
	current = shell->memory;
	while (current)
	{
		next = current->next_ptr;
		free(current);
		current = next;
	}
	shell->memory = NULL;
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
	shell->commands = NULL;
	shell->env_copy = duplicate_env(env);
	if (!shell->env_copy)
	{
		free(shell->expand);
		free(shell->sbstr);
		free(shell);
		return (NULL);
	}
	return (shell->exit_status = 0, shell);
}
