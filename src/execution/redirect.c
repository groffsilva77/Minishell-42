/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:59:35 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 13:55:12 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_redirection(t_command *cmd, t_shell *shell)
{
	int	fd;

	(void)shell;
	if (cmd->input_file && *cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd < 0)
		{
			perror("Input redirection failed");
			return (-1);
		}
		cmd->input_fd = fd;
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			perror("Dup in failed");
			close(fd);
			return (-1);
		}
	}
	return (0);
}

static int	handle_output_redirection(t_command *cmd, t_shell *shell)
{
	int	fd;

	(void)shell;
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
		cmd->output_fd = fd;
		if (dup2(fd, STDOUT_FILENO) < 0)
		{
			perror("dup2 failed");
			close(fd);
			return (-1);
		}
	}
	return (0);
}

int	handle_redirections(t_command *cmd, t_shell *shell)
{
	if (cmd->input_file)
	{
		if (handle_input_redirection(cmd, shell) < 0)
			return (cleanup_shell(shell), -1);
	}
	if (cmd->output_file)
	{
		if (handle_output_redirection(cmd, shell) < 0)
			return (cleanup_shell(shell), -1);
	}
	return (0);
}
