/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 12:58:40 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/08 19:07:14 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void free_shell(t_shell *shell)
{
    int i;

    if (!shell)
        return;
	//printf("free_shell: liberating shell=%p\n", shell);
    if (shell->expand)
	{
		printf("free_shell: liberating expand=%p\n", shell->expand);
        ft_free(shell, shell->expand);
		shell->expand = NULL;
	}
    if (shell->sbstr)
	{
		printf("free_shell: liberating sbstr=%p\n", shell->sbstr);
        ft_free(shell, shell->sbstr);
		shell->sbstr = NULL;
	}
    if (shell->env_copy)
    {
        i = 0;
        while (shell->env_copy[i])
		{
			printf("free_shell: liberating env_copy[%d]=%p (%s)\n", i, shell->env_copy[i], shell->env_copy[i]);
			ft_free(shell, shell->env_copy[i]);
			shell->env_copy[i] = NULL;
			i++;
		}
		printf("free_shell: liberating env_copy=%p\n", shell->env_copy);
        ft_free(shell, shell->env_copy);
		shell->env_copy = NULL;
    }
	printf("free_shell: liberating shell=%p\n", shell);
    free(shell);
}


char	**duplicate_env(char **env, t_shell *shell)
{
	int		i;
	char	**copy;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
		i++;
	copy = fts_malloc(shell, sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = fts_strdup(shell, env[i]);
		if (!copy[i])
		{
			while (i > 0)
				ft_free(shell, copy[--i]);
			return (ft_free(shell, copy), NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;
	int		i;

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
	shell->env_copy = duplicate_env(env, shell);
	if (!shell->env_copy)
	{
		free(shell->expand);
		free(shell->sbstr);
		free(shell);
		return (NULL);
	}
	i = 0;
    while (shell->env_copy[i])
    {
        //printf("init_shell: env_copy[%d]=%s\n", i, shell->env_copy[i]);
        i++;
    }
    //printf("init_shell: total size=%d\n", i);
	shell->exit_status = 0;
	return (shell);
}
