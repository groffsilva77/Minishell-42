/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:36:22 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/12 16:16:05 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	execute_builtin(t_command *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (the_cd(cmd->args, shell));
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (the_echo(cmd->args, shell));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (the_pwd(shell));
	if (!ft_strcmp(cmd->args[0], "export"))
		return (the_export(cmd->args, shell));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (the_unset(cmd->args, shell));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (the_env(shell));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (the_exit(cmd->args, shell));
	return (1);
}
