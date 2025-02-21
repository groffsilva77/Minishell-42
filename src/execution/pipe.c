/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:39:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/21 17:32:05 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_command *cmd);

static void	child_process(t_command *cmd, int *fd_in, int *pipe_fd,
		t_shell *shell)
{
	if (*fd_in != -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if (pipe_fd[1] != -1)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	execute_command(cmd, shell);
	exit(shell->exit_status);
}

static void	parent_process(int *fd_in, int *pipe_fd)
{
	if (*fd_in != -1)
		close(*fd_in);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (pipe_fd[0] != -1)
		*fd_in = pipe_fd[0];
	else
		*fd_in = -1;
}

static void	wait_children(t_shell *shell)
{
	int	status;
	int	last_pid;

	last_pid = wait(&status);
	while (last_pid > 0)
		last_pid = wait(&status);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

void	execute_pipeline(t_command *cmd, t_shell *shell)
{
	int		pipe_fd[2];
	int		fd_in;
	pid_t	pid;

	fd_in = -1;
	while (cmd)
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
		if (cmd->next && pipe(pipe_fd) < 0)
			return (perror("pipe"));
		pid = fork();
		if (pid < 0)
			return (perror("fork"));
		if (pid == 0)
			child_process(cmd, &fd_in, pipe_fd, shell);
		else
			parent_process(&fd_in, pipe_fd);
		cmd = cmd->next;
	}
	wait_children(shell);
}

void	execute_single_command(t_command *cmd, t_shell *shell)
{
	int	stdout_backup;
	int	stderr_backup;

	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]) && !cmd->next)
	{
		stdout_backup = dup(STDOUT_FILENO);
		stderr_backup = dup(STDERR_FILENO);
		if (setup_redirections(cmd) < 0)
		{
			dup2(stdout_backup, STDOUT_FILENO);
			dup2(stderr_backup, STDERR_FILENO);
			close(stdout_backup);
			close(stderr_backup);
			return ;
		}
		execute_builtin(cmd, shell);
		dup2(stdout_backup, STDOUT_FILENO);
		dup2(stderr_backup, STDERR_FILENO);
		close(stdout_backup);
		close(stderr_backup);
	}
	else
		execute_pipeline(cmd, shell);
}
