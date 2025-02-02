/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:59:35 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/31 17:11:17 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (handle_input_redirection(cmd) < 0)
		return (-1);
	if (handle_output_redirection(cmd) < 0)
		return (-1);
	return (0);
}

int	setup_redirections(t_command *cmd)
{
	if (handle_redirections(cmd) < 0)
		return (-1);
	return (0);
}
