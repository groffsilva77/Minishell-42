/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:39:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 14:52:27 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_children(t_shell *shell)
{
	int	status;
	int	last_pid;
	int	count;

	signal(SIGINT, SIG_IGN);
	last_pid = wait(&status);
	count = 0;
	while (last_pid > 0)
	{
		count++;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			shell->exit_status = 130;
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		last_pid = wait(&status);
	}
	signal(SIGINT, sigint_handler);
}

static void	setup_pipe_and_fork(t_command *cmd, int *pipe_fd,
				t_shell *shell, pid_t *pid)
{
	if (cmd->next && pipe(pipe_fd) < 0)
		return (perror("pipe"));
	if (pipe_fd[0] != -1)
		track_fd(shell, pipe_fd[0]);
	if (pipe_fd[1] != -1)
		track_fd(shell, pipe_fd[1]);
	*pid = fork();
	if (*pid < 0)
		return (perror("fork"));
}

static void	execute_the_command(t_command *cmd, int *fd_in, t_shell *shell)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (cmd->is_heredoc)
	{
		cmd->heredoc_fd = handle_heredoc(cmd, shell);
		if (cmd->heredoc_fd < 0)
		{
			shell->exit_status = 130;
			return ;
		}
	}
	setup_pipe_and_fork(cmd, pipe_fd, shell, &pid);
	if (pid == 0)
		child_process(cmd, fd_in, pipe_fd, shell);
	else
		parent_process(fd_in, pipe_fd, shell);
}

void	execute_pipeline(t_command *cmd, t_shell *shell)
{
	int			fd_in;
	t_command	*current;

	fd_in = -1;
	while (cmd)
	{
		execute_the_command(cmd, &fd_in, shell);
		cmd = cmd->next;
	}
	wait_children(shell);
	current = cmd;
	while (current)
	{
		if (current->is_heredoc && current->heredoc_fd >= 0)
			close_and_untrack_fd(shell, &current->heredoc_fd);
		current = current->next;
	}
}

void	execute_single_command(t_command *cmd, t_shell *shell)
{
	if (!cmd || (!cmd->args && !cmd->is_heredoc))
		return ;
	if (cmd->is_heredoc && !cmd->args)
	{
		cmd->heredoc_fd = handle_heredoc(cmd, shell);
		if (cmd->heredoc_fd >= 0)
			close_and_untrack_fd(shell, &cmd->heredoc_fd);
		return ;
	}
	if (cmd->is_heredoc && cmd->heredoc_fd >= 0)
	{
		if (!is_fd_tracked(shell, cmd->heredoc_fd))
			track_fd(shell, cmd->heredoc_fd);
	}
	if (cmd->args && cmd->args[0] && is_builtin(cmd->args[0]) && !cmd->next
		&& !cmd->output_file && !cmd->input_file)
		execute_builtin(cmd, shell);
	else
		execute_pipeline(cmd, shell);
	close_all_unused_fds(shell, cmd);
}
