/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:41:09 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/19 14:51:14 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_delimiter(char *delim)
{
	int		expand_vars;
	size_t	len;

	expand_vars = 1;
	len = ft_strlen(delim);
	if (len >= 2 && (delim[0] == '\'' || delim[0] == '"')
		&& delim[0] == delim[len - 1])
	{
		delim[len - 1] = '\0';
		ft_memmove(delim, delim + 1, len);
		expand_vars = 0;
	}
	return (expand_vars);
}

void	process_heredoc_line(char *line, int pipe_write_fd,
					t_shell *shell, int expand_vars)
{
	char	*expanded_line;

	expanded_line = expand_tokens(shell, line, expand_vars);
	free(line);
	if (!expanded_line)
	{
		close(pipe_write_fd);
		cleanup_shell(shell);
		exit(1);
	}
	write(pipe_write_fd, expanded_line, ft_strlen(expanded_line));
	write(pipe_write_fd, "\n", 1);
	free(expanded_line);
}
