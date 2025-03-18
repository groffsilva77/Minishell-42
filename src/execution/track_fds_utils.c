/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_fds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:02:14 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/18 13:04:02 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_unused_fds(t_shell *shell, t_command *cmd)
{
	t_command	*current;

	current = cmd;
	while (current)
	{
		if (current->is_heredoc && current->heredoc_fd >= 0)
			close_and_untrack_fd(shell, &current->heredoc_fd);
		current = current->next;
	}
}

int	is_fd_tracked(t_shell *shell, int fd)
{
	int	i;

	i = 0;
	while (i < shell->fd_tracker.count)
	{
		if (shell->fd_tracker.fds[i] == fd)
			return (1);
		i++;
	}
	return (0);
}
