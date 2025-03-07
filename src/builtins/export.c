/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:02:33 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/07 12:10:25 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_existing_var(char *name, char *value_ex, t_shell *shell)
{
	int		i;
	char	*new_value;
	char	*temp;

	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], name, ft_strlen(name)) == 0
			&& shell->env_copy[i][ft_strlen(name)] == '=')
		{
			temp = ft_strjoin(name, "=");
			if (!temp)
				return (1);
			new_value = ft_strjoin(temp, value_ex);
			free(temp);
			if (!new_value)
				return (1);
			free(shell->env_copy[i]);
			shell->env_copy[i] = new_value;
			shell->exit_status = 0;
			return (0);
		}
		i++;
	}
	return (1);
}

static char	**copy_env(char **env_copy, int size)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env_copy[i])
	{
		new_env[i] = ft_strdup(env_copy[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static int	add_new_var(char *name, char *value_ex, t_shell *shell)
{
	char	**new_env;
	char	*temp;
	char	*new_value;
	int		i;

	i = 0;
	while (shell->env_copy[i])
		i++;
	new_env = copy_env(shell->env_copy, i + 1);
	if (!new_env)
		return (1);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (free(new_env), 1);
	new_value = ft_strjoin(temp, value_ex);
	free(temp);
	if (!new_value)
		return (free(new_env), 1);
	new_env[i] = new_value;
	new_env[i + 1] = NULL;
	free(shell->env_copy);
	shell->env_copy = new_env;
	shell->exit_status = 0;
	return (0);
}

int	the_export(char **args, t_shell *shell)
{
	const char	*eq_position;
	char		*name;
	char		*value_ex;
	size_t		name_len;

	if (!args[1])
		return (the_env(shell));
	eq_position = ft_strchr(args[1], '=');
	if (!eq_position)
		return (0);
	name_len = eq_position - args[1];
	name = malloc(name_len + 1);
	if (!name)
		return (1);
	ft_memcpy(name, args[1], name_len);
	name[name_len] = '\0';
	value_ex = ft_strdup(eq_position + 1);
	if (!value_ex)
		return (free(name), 1);
	if (update_existing_var(name, value_ex, shell) != 0)
	{
		if (add_new_var(name, value_ex, shell) != 0)
			return (free(name), free(value_ex), 1);
	}
	return (free(name), free(value_ex), 0);
}
