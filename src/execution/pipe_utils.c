/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:08:57 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/06 17:21:23 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_heredoc(t_command *cmd)
{
	if (cmd->is_heredoc && cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) < 0)
		{
			perror("heredoc dup2 failed\n");
			exit(1);
		}
		close(cmd->heredoc_fd);
	}
}

static void	setup_pipes(t_command *cmd, int *fd_in, int *pipe_fd)
{
	if (*fd_in != -1 && !cmd->is_heredoc)
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
}

void	child_process(t_command *cmd, int *fd_in, int *pipe_fd,
			t_shell *shell)
{
	if (setup_redirections(cmd) < 0)
		exit(1);
	setup_heredoc(cmd);
	setup_pipes(cmd, fd_in, pipe_fd);
	execute_command(cmd, shell);
	exit(shell->exit_status);
}
