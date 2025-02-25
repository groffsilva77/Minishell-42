/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:36:22 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/19 15:47:56 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3)
		|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4)
		|| !ft_strncmp(cmd, "exit", 5));
}

int	execute_builtin(t_command *cmd, t_shell *shell)
{
	if (!cmd->args[0])
		return (0);
	if (cmd->output_file || cmd->input_file || cmd->is_heredoc)
		if (setup_redirections(cmd) < 0)
			return (1);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (the_cd(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (the_echo(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (the_pwd(shell));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (the_export(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (the_unset(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (the_env(shell));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (the_exit(cmd->args, shell));
	return (0);
}
