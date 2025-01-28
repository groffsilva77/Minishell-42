/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:39:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/28 17:52:51 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	handle_redirections(t_command *cmd)
{
	int	fd;
	int	flags;

	if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("Input redirection failed");
			return (-1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd->output_file)
	{
		if (cmd->type == CMD_APPEND)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		fd = open(cmd->output_file, flags, 0644);
		if (fd < 0)
		{
			perror("Output redirection failed");
			return (-1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	return (0);
}

void	create_process(t_command *cmd, t_exec_context *ctx, t_shell *shell)
{
	if (ctx->prev_fd != -1)
	{
		dup2(ctx->prev_fd, STDIN_FILENO);
		close(ctx->prev_fd);
	}
	if (cmd->next)
		dup2(ctx->pipe_fds[1], STDOUT_FILENO);
	close(ctx->pipe_fds[0]);
	close(ctx->pipe_fds[1]);
	if (handle_redirections(cmd) < 0)
		exit(1);
	execve(cmd->args[0], cmd->args, shell->env_copy);
	perror("Execve failed");
	exit(127);
}

int	setup_pipes(t_exec_context *ctx)
{
	if (pipe(ctx->pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	return (0);
}

void	execute_pipeline(t_command *commands, t_shell *shell)
{
	t_exec_context	ctx;
	int				status;

	ctx.prev_fd = -1;
	while (commands)
	{
		if (commands->next && setup_pipes(&ctx) < 0)
			return ;
		ctx.pid = fork();
		if (ctx.pid < 0)
			return (perror("fork failed"));
		if (ctx.pid == 0)
			create_process(commands, &ctx, shell);
		close(ctx.pipe_fds[1]);
		if (ctx.prev_fd != -1)
			close(ctx.prev_fd);
		ctx.prev_fd = ctx.pipe_fds[0];
		commands = commands->next;	
	}
	while (wait(&status) > 0)
		;
	shell->exit_status = WEXITSTATUS(status);
}
