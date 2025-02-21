/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:04:10 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/21 16:33:44 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_absolute_path(const char *command)
{
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

char	*search_in_path(const char *command, char *path)
{
	char	**dir;
	char	*full_path;
	int		i;

	dir = ft_split(path, ':');
	if (!dir)
		return (NULL);
	i = -1;
	while (dir[++i])
	{
		full_path = malloc(ft_strlen(dir[i]) + ft_strlen(command) + 2);
		if (!full_path)
			return (ft_free_array(dir), NULL);
		ft_strcpy(full_path, dir[i]);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
			return (ft_free_array(dir), full_path);
		free(full_path);
	}
	return (ft_free_array(dir), NULL);
}

char	*find_command_path(const char *command, char **envp)
{
	int		i;
	char	*result;

	if (!command)
		return (NULL);
	if (ft_strchr(command, '/') != NULL)
		return (resolve_absolute_path(command));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			result = search_in_path(command, envp[i] + 5);
			ft_putstr_fd("Path found: ", 2);
			ft_putendl_fd(result ? result : "NULL", 2);
			return(result);
		}
	}
	ft_putstr_fd("No PATH in envp\n", 2);
	return (NULL);
}
