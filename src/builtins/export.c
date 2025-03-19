/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:02:33 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/19 17:35:23 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (name[0] == '=' || name[0] == '+' || name[0] == '~' || name[0] == '-')
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	update_existing_var(char *name, char *value_ex, t_shell *shell)
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

	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size && env_copy[i])
	{
		new_env[i] = ft_strdup(env_copy[i]);
		if (!new_env[i])
		{
			ft_free_array(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	add_new_var(char *name, char *value_ex, t_shell *shell)
{
	char	**new_env;
	char	*temp;
	char	*new_value;
	int		i;

	i = 0;
	while (shell->env_copy[i])
		i++;
	new_env = copy_env(shell->env_copy, i);
	if (!new_env)
		return (1);
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (ft_free_array(new_env), 1);
	new_value = ft_strjoin(temp, value_ex);
	free(temp);
	if (!new_value)
		return (ft_free_array(new_env), 1);
	new_env[i] = new_value;
	new_env[i + 1] = NULL;
	ft_free_array(shell->env_copy);
	shell->env_copy = new_env;
	shell->exit_status = 0;
	return (0);
}

int	the_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
		return (the_env(shell));
	i = 1;
	while (args[i])
	{
		if (process_export(args[i], shell) != 0)
			return (1);
		i++;
	}
	return (0);
}
