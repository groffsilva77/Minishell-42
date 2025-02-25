/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:53:16 by ggroff-d          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/02/20 14:02:06 by ytavares         ###   ########.fr       */
=======
/*   Updated: 2025/02/18 19:50:47 by ggroff-d         ###   ########.fr       */
>>>>>>> 61e53790d7d686fd655c7b05c5e64901fb0963bc
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_command *cmd, t_shell *shell)
{
	char	*path;
	char	*expanded_cmd;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(EXIT_FAILURE);
	if (cmd->args[0][0] == '$')
	{
		expanded_cmd = expand_tokens(shell ,cmd->args[0], 1);
		if (!expanded_cmd || !*expanded_cmd)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(cmd->args[0], 2);
			free(expanded_cmd);
			exit(127);
		}
		free(cmd->args[0]);
		cmd->args[0] = expanded_cmd;
	}
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, shell);
		exit(EXIT_SUCCESS);
	}
	path = find_command_path(cmd->args[0], shell->env_copy);
	if (!path)
	{
		ft_putstr_fd("minishell: command not found: \n", 2);
		ft_putendl_fd(cmd->args[0], 2);
		exit(127);
	}
	if (execve(path, cmd->args, shell->env_copy) < 0)
	{
		free(path);
		perror("execve");
		exit(126);
	}
}

// void	create_process(t_command *cmd, t_exec_context *ctx, t_shell *shell)
// {
// 	if (cmd->args[0] && cmd->args[0][0] == '$')
// 		get_env_value(cmd->args[0]);
// 	if (ctx->prev_fd != -1)
// 	{
// 		dup2(ctx->prev_fd, STDIN_FILENO);
// 		close(ctx->prev_fd);
// 	}
// 	if (setup_redirections(cmd) < 0)
// 		exit(1);
// 	if (cmd->next && !cmd->output_file)
// 		dup2(ctx->pipe_fds[1], STDOUT_FILENO);
// 	close(ctx->pipe_fds[0]);
// 	close(ctx->pipe_fds[1]);
// 	execute_command(cmd, shell);
// }
