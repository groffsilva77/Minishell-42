/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:16 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/17 16:52:32 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_command(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	return (1);
}

static int	execute_builtin_command(t_command *cmd, t_shell *shell)
{
	return (execute_builtin(cmd, shell));
}

static void	handle_cmd_not_found(t_command *cmd)
{
	struct stat	st;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (stat(cmd->args[0], &st) == 0 && S_ISDIR(st.st_mode))
			ft_putendl_fd(": Is a directory", 2);
		else if (access(cmd->args[0], X_OK) == -1)
			ft_putendl_fd(": Permission denied", 2);
		else
			ft_putendl_fd(": command not found", 2);
	}
	else
		ft_putendl_fd(": command not found", 2);
	exit(127);
}

static void	handle_execve_failure(t_command *cmd, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	if (errno == EISDIR)
		ft_putendl_fd(": Is a directory", 2);
	else if (errno == EACCES)
		ft_putendl_fd(": Permission denied", 2);
	else
		ft_putendl_fd(": execve failed", 2);
	free(path);
	exit(126);
}

void	execute_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	int		status;

	if (!validate_command(cmd))
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
	{
		status = execute_builtin_command(cmd, shell);
		return ;
	}
	path = find_command_path(cmd->args[0], shell->env_copy);
	if (!path)
		handle_cmd_not_found(cmd);
	if (execve(path, cmd->args, shell->env_copy) < 0)
		handle_execve_failure(cmd, path);
	free(path);
}
