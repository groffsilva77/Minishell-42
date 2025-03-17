/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:39:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/17 16:52:26 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_process(int *fd_in, int *pipe_fd, t_shell *shell)
{
	if (*fd_in != -1)
		close_and_untrack_fd(shell, fd_in);
	if (pipe_fd[1] != -1)
		close_and_untrack_fd(shell, &pipe_fd[1]);
	if (pipe_fd[0] != -1)
		*fd_in = pipe_fd[0];
	else
		*fd_in = -1;
}

static void	wait_children(t_shell *shell)
{
	int	status;
	int	last_pid;
	int	count = 0;

	signal(SIGINT, SIG_IGN);
	last_pid = wait(&status);
	while (last_pid > 0)
	{
		count++;
		printf("Child %d terminated\n", last_pid);
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
	printf("Total children waited: %d\n", count);
	signal(SIGINT, sigint_handler);
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
		printf("After handle_heredoc, heredoc_fd = %d\n", cmd->heredoc_fd);
		if (cmd->heredoc_fd < 0)
		{
			shell->exit_status = 130;
			return ;
		}
	}
	if (cmd->next && pipe(pipe_fd) < 0)
		return (perror("pipe"));
	if (pipe_fd[0] != -1)
		track_fd(shell, pipe_fd[0]);
	if (pipe_fd[1] != -1)
		track_fd(shell, pipe_fd[1]);
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
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
	printf("Before wait_children, tracked FDs: ");
    for (int i = 0; i < shell->fd_tracker.count; i++)
        printf("%d ", shell->fd_tracker.fds[i]);
    printf("\n");
	wait_children(shell);
	current = cmd;
	while (current)
	{
		if (current->is_heredoc && current->heredoc_fd >= 0)
		{
			close_and_untrack_fd(shell, &current->heredoc_fd);
			printf("Closed heredoc_fd %d after wait\n", current->heredoc_fd);
		}
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
		printf("After handle_heredoc, heredoc_fd = %d\n", cmd->heredoc_fd);
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
