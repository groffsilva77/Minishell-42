/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:16 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/26 16:34:38 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	*expanded_cmd;
	struct	stat st;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(EXIT_FAILURE);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, shell);
		exit(EXIT_SUCCESS);
	}
	path = find_command_path(cmd->args[0], shell->env_copy);
	if (!path)
	{
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
	if (execve(path, cmd->args, shell->env_copy) < 0)
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
}
