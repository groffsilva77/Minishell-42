/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:59:35 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/05 17:57:41 by ggroff-d         ###   ########.fr       */
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
		if (!line)
			break ;
		trimmed_line = fts_strtrim(line);
		if (ft_strcmp(trimmed_line, cmd->heredoc_delim) == 0)
		{
			ft_putstr_fd("DEBUG: Found delimiter, breaking\n", 2);
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
		if (cmd->append_output)
			fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
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
