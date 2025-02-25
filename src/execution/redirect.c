/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:59:35 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/25 13:54:38 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_command *cmd)
{
	char	*line;
	char	*trimmed_line;

	if (pipe(cmd->heredoc_pipe) == -1)
		return (perror("heredoc pipe failed"), -1);
	while (1)
	{
		line = readline("> ");
		trimmed_line = fts_strtrim(line);
		if (!line || ft_strcmp(trimmed_line, cmd->heredoc_delim) == 0)
		{
			free(line);
			free(trimmed_line);
			break ;
		}
		write(cmd->heredoc_pipe[1], line, ft_strlen(line));
		write(cmd->heredoc_pipe[1], "\n", 1);
		free(line);
		free(trimmed_line);
	}
	close(cmd->heredoc_pipe[1]);
	return (cmd->heredoc_pipe[0]);
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
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("Dup in failed");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	handle_output_redirection(t_command *cmd)
{
	int	fd;

	if (cmd->output_file && *cmd->output_file)
	{
		if (cmd->type == CMD_APPEND)
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (cmd->type == CMD_REDIR_OUT)
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("open failed");
			return (-1);
		}
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close(fd);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	int		fd;

	if (cmd->is_heredoc == CMD_HEREDOC && cmd->heredoc_fd != -1)
	{
		if (dup2(cmd->heredoc_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 heredoc");
			close(cmd->heredoc_fd);
			return (-1);
		}
		close(cmd->heredoc_fd);
	}
	if (cmd->input_file)
	{
		if (handle_input_redirection(cmd) < 0)
			return (-1);
	}
	if (cmd->output_file)
	{
		if (handle_output_redirection(cmd) < 0)
			return (-1);
	}
	return (0);
}

int	setup_redirections(t_command *cmd)
{
	return (handle_redirections(cmd));
}
