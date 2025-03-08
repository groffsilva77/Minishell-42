/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:39:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/08 18:07:35 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	execute_the_command(t_command *cmd, int *fd_in, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->is_heredoc)
	{
		cmd->heredoc_fd = handle_heredoc(cmd);
		if (cmd->heredoc_fd < 0)
			exit(1);
	}
	if (cmd->next && pipe(pipe_fd) < 0)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
		child_process(cmd, fd_in, pipe_fd, shell);
	else
		parent_process(fd_in, pipe_fd);
}

void	execute_pipeline(t_command *cmd, t_shell *shell)
{
	int		fd_in;

	fd_in = -1;
	while (cmd)
	{
		execute_the_command(cmd, &fd_in, shell);
		cmd = cmd->next;
	}
	wait_children(shell);
}


void	execute_single_command(t_command *cmd, t_shell *shell)
{
	//int	heredoc_fd;

	if (!cmd)
		return ;
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]) && !cmd->next
		&& !cmd->output_file && !cmd->input_file)
		execute_builtin(cmd, shell);
	else
		execute_pipeline(cmd, shell);
}
