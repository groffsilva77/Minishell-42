/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:16 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/28 18:00:14 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simple_command(t_command *cmd, t_shell *shell)
{
	t_exec_context	ctx;
	int				status;

	ctx.pid = fork();
	if (ctx.pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (ctx.pid == 0)
	{
		if (handle_redirections(cmd) < 0)
			exit(1);
		execve(cmd->args[0], cmd->args, shell->env_copy);
		perror("Execve failed");
		exit(127);
	}
	else
	{
		waitpid(ctx.pid, &status, 0);
		shell->exit_status = WEXITSTATUS(status);
	}
}

void	execute_commands(t_command *commands, t_shell *shell)
{
	if (!commands)
		return ;
	if (commands->next)
		execute_pipeline(commands, shell);
	else
		execute_simple_command(commands, shell);
}