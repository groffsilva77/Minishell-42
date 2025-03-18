/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:23:11 by ytavares          #+#    #+#             */
/*   Updated: 2025/03/18 12:54:43 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_existing_env_var(t_shell *shell, const char *name,
				 char *new_var)
{
	int	i;

	i = 0;
	while (shell->env_copy[i])
	{
		if (ft_strncmp(shell->env_copy[i], name, ft_strlen(name)) == 0
			&& shell->env_copy[i][ft_strlen(name)] == '=')
		{
			free(shell->env_copy[i]);
			shell->env_copy[i] = new_var;
			return ;
		}
		i++;
	}
	if (!ft_realloc_array(shell->env_copy, i + 2, new_var, shell))
		free(new_var);
	else
		shell->env_copy[i] = new_var;
	shell->env_copy[i + 1] = NULL;
}

static void	update_env_var(t_shell *shell, const char *name, const char *val)
{
	char	*new_var;
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return ;
	new_var = ft_strjoin(temp, val);
	free(temp);
	if (!new_var)
		return ;
	update_existing_env_var(shell, name, new_var);
}

static int	change_directory(char *new_dir, t_shell *shell, char *atl_dir)
{
	char	*current_dir;

	if (chdir(new_dir) != 0)
	{
		perror("cd");
		shell->exit_status = 1;
		return (1);
	}
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
	{
		shell->exit_status = 1;
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
	store_home = get_env_value(shell, "HOME");
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
	int		the_result;

	if (!shell || !args || getcwd(store_atl_dir, sizeof(store_atl_dir)) == NULL)
		return (1);
	if (!args[1])
	{
		if (handle_no_args(shell, &new_path_dir) != 0)
			return (1);
	}
	else
	{
		new_path_dir = ft_strdup(args[1]);
		if (!new_path_dir)
			return (shell->exit_status = 1, 1);
	}
	the_result = change_directory(new_path_dir, shell, store_atl_dir);
	return (free(new_path_dir), the_result);
}
