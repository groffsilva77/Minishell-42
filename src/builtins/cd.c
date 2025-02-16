/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:23:11 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/16 18:54:44 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(t_shell *shell, const char *name, const char *value)
{
	int		i;
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return ;
	new_var = ft_strjoin(temp, value);
	free(temp);
	if (!new_var)
		return ;
	i = 0;
	while (shell->env_copy[i])
	{
		if (!name || !shell->env_copy[i])
			continue ;
		if (ft_strlen(shell->env_copy[i]) >= ft_strlen(name) + 1
			&& ft_strncmp(shell->env_copy[i], name, ft_strlen(name)) == 0
			&& shell->env_copy[i][ft_strlen(name)] == '=')
		{
			shell->env_copy[i] = new_var;
			free(shell->env_copy[i]);
			return ;
		}
		i++;
	}
	if (!ft_realloc_array(shell->env_copy, i + 2, new_var, shell))
	{
		free(new_var);
		return ;
	}
	shell->env_copy[i] = new_var;
	shell->env_copy[i + 1] = NULL;
}

static int	change_directory(char *new_dir, t_shell *shell, char *atl_dir)
{
	char	*current_dir;

	if (chdir(new_dir) != 0)
	{
		perror("cd");
		shell->exit_status = 1;
		free(new_dir);
		return (1);
	}
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		shell->exit_status = 1;
		free(new_dir);
		return (1);
	}
	update_env_var(shell, "OLDPWD", atl_dir);
	update_env_var(shell, "PWD", new_dir);
	free(current_dir);
	shell->exit_status = 0;
	return (0);
}

static int	handle_no_args(t_shell *shell, char **new_path_dir)
{
	char	*store_home;

	if (!shell || !new_path_dir)
		return (1);
	store_home = get_env_value("HOME");
	if (!store_home || !*store_home)
	{
		ft_putendl_fd("cd: HOME is not defined", 2);
		shell->exit_status = 1;
		return (1);
	}
	*new_path_dir = ft_strdup(store_home);
	if (!*new_path_dir)
	{
		shell->exit_status = 1;
		return (1);
	}
	return (0);
}

int	the_cd(char **args, t_shell *shell)
{
	char	*new_path_dir;
	char	store_atl_dir[1024];

	if (!shell || !args)
		return (1);
	if (getcwd(store_atl_dir, sizeof(store_atl_dir)) == NULL)
	{
		shell->exit_status = 1;
		return (1);
	}
	if (!args[1])
	{
		if (handle_no_args(shell, &new_path_dir) != 0)
			return (1);
	}
	else
	{
		new_path_dir = ft_strdup(args[1]);
		if (!new_path_dir)
		{
			shell->exit_status = 1;
			return (free(new_path_dir), 1);
		}
	}
	return (change_directory(new_path_dir, shell, store_atl_dir));
}
