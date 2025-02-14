/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:16 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/14 17:25:40 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_env_var(t_command *cmd, t_shell *shell)
// {
// 	char	*var_name;
// 	char	*var_value;

// 	(void)shell;
// 	if (cmd->args[0][0] == '$')
// 	{
// 		var_name = cmd->args[0] + 1;
// 		var_value = getenv(var_name);
// 		if (!var_value)
// 			printf("\n");
// 		exit(0);
// 	}
// }

void	execute_command(t_command *cmd, t_shell *shell)
{
	char	*path;

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
		ft_putstr_fd("minishell: command not found: \n", 2);
		ft_putendl_fd(cmd->args[2], 2);
		exit(127);
	}
	if (execve(path, cmd->args, shell->env_copy) < 0)
	{
		free(path);
		perror("execve");
		exit(126);
	}
}

void	create_process(t_command *cmd, t_exec_context *ctx, t_shell *shell)
{
	if (cmd->args[0] && cmd->args[0][0] == '$')
		get_env_value(cmd->args[0]);
	if (ctx->prev_fd != -1)
	{
		dup2(ctx->prev_fd, STDIN_FILENO);
		close(ctx->prev_fd);
	}
	if (cmd->next)
		dup2(ctx->pipe_fds[1], STDOUT_FILENO);
	close(ctx->pipe_fds[0]);
	close(ctx->pipe_fds[1]);
	if (setup_redirections(cmd) < 0)
		exit(1);
	execute_command(cmd, shell);
}
