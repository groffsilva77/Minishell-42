/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:59:35 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/16 18:46:55 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc(t_command *cmd)
{
	int		pipe_fds[2];
	char	*line;

	if (pipe(pipe_fds) == -1)
		return (perror("Error: pipe failed while creating heredoc"), -1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, cmd->heredoc_delim,
				ft_strlen(cmd->heredoc_delim)) == 0)
		{
			free(line);
			break ;
		}
		if (*line)
			add_history(cmd->heredoc_delim);
		write(pipe_fds[1], line, ft_strlen(line));
		write(pipe_fds[1], "\n", 1);
		free(line);
	}
	close(pipe_fds[1]);
	return (pipe_fds[0]);
}

int	handle_input_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->input_file && *cmd->input_file)
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
	return (0);
}

int	handle_output_redirection(t_command *cmd)
{
	int	fd;
	int	flags;

	if (cmd->output_file && *cmd->output_file)
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

int	handle_redirections(t_command *cmd)
{
	int		fd;
	pid_t	pid;

	if (cmd->is_heredoc)
	{
		pid = fork();
		if (pid == -1)
			return (perror("Error: fork invalid in heredoc"), -1);
		if (pid == 0)
		{
			fd = handle_heredoc(cmd);
			if (fd >= 0)
			{
				dup2(fd, STDIN_FILENO);
				close(fd);
			}
			exit(0);
		}
		return (waitpid(pid, NULL, 0), 0);
	}
	if (handle_input_redirection(cmd) < 0)
		return (-1);
	if (handle_output_redirection(cmd) < 0)
		return (-1);
	return (0);
}

int	setup_redirections(t_command *cmd)
{
	return (handle_redirections(cmd));
}
