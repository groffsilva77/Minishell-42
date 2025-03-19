/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:55:50 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 16:42:18 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_child_process(int pipe_write_fd, char *delim,
				t_shell *shell)
{
	char	*line;
	int		expand_vars;

	expand_vars = process_heredoc_delimiter(delim);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(line, pipe_write_fd, shell, expand_vars);
	}
	close(pipe_write_fd);
	exit_process(shell, 0);
}

static int	heredoc_parent_process(pid_t child_pid, int pipe_read_fd,
					t_shell *shell)
{
	int					status;
	struct sigaction	old_act;
	struct sigaction	temp_act;

	sigaction(SIGINT, NULL, &old_act);
	sigemptyset(&temp_act.sa_mask);
	temp_act.sa_flags = 0;
	temp_act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &temp_act, NULL);
	waitpid(child_pid, &status, 0);
	sigaction(SIGINT, &old_act, NULL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		shell->exit_status = 130;
		close_and_untrack_fd(shell, &pipe_read_fd);
		set_signal_state(SIGINT);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		return (-1);
	}
	return (pipe_read_fd);
}

static int	start_heredoc_child(t_command *cmd, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("heredoc fork failed");
		close_and_untrack_fd(shell, &cmd->heredoc_pipe[0]);
		close_and_untrack_fd(shell, &cmd->heredoc_pipe[1]);
		return (-1);
	}
	if (pid == 0)
	{
		close_and_untrack_fd(shell, &cmd->heredoc_pipe[0]);
		heredoc_child_process(cmd->heredoc_pipe[1], cmd->heredoc_delim, shell);
		exit_process(shell, 1);
	}
	return (pid);
}

int	handle_heredoc(t_command *cmd, t_shell *shell)
{
	pid_t	pid;
	int		result;

	if (pipe(cmd->heredoc_pipe) == -1)
		return (perror("heredoc pipe failed"), -1);
	track_fd(shell, cmd->heredoc_pipe[0]);
	track_fd(shell, cmd->heredoc_pipe[1]);
	pid = start_heredoc_child(cmd, shell);
	if (pid == -1)
		return (-1);
	close_and_untrack_fd(shell, &cmd->heredoc_pipe[1]);
	result = heredoc_parent_process(pid, cmd->heredoc_pipe[0], shell);
	if (result < 0)
	{
		close_and_untrack_fd(shell, &cmd->heredoc_pipe[0]);
		return (-1);
	}
	cmd->heredoc_fd = result;
	return (cmd->heredoc_fd);
}
