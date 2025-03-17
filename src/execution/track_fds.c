/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 13:01:41 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/17 16:57:27 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd_tracker(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < MAX_FD_TRACKED)
	{
		shell->fd_tracker.fds[i] = -1;
		i++;
	}
	shell->fd_tracker.count = 0;
	shell->fd_tracker.initialized = 1;
}

int	track_fd(t_shell *shell, int fd)
{
	if (fd < 0)
		return (0);
	if (!shell->fd_tracker.initialized)
		init_fd_tracker(shell);
	if (shell->fd_tracker.count >= MAX_FD_TRACKED)
		return (0);
	shell->fd_tracker.fds[shell->fd_tracker.count++] = fd;
	return (1);
}

void	untrack_fd(t_shell *shell, int fd)
{
	int	i;
	int	j;

	if (fd < 0 || !shell->fd_tracker.initialized)
		return ;
	i = 0;
	while (i < shell->fd_tracker.count)
	{
		if (shell->fd_tracker.fds[i] == fd)
		{
			j = i;
			while (j < shell->fd_tracker.count - 1)
			{
				shell->fd_tracker.fds[j] = shell->fd_tracker.fds[j + 1];
				j++;
			}
			shell->fd_tracker.fds[shell->fd_tracker.count - 1] = -1;
			shell->fd_tracker.count--;
			return ;
		}
		i++;
	}
}

void	close_and_untrack_fd(t_shell *shell, int *fd)
{
	if (*fd >= 3)
	{
		close(*fd);
		untrack_fd(shell, *fd);
	}
	*fd = -1;
}

void	close_all_tracked_fds(t_shell *shell)
{
	int	i;
	int	fd;

	if (!shell->fd_tracker.initialized)
		return ;
	i = 0;
	while (i < shell->fd_tracker.count)
	{
		fd = shell->fd_tracker.fds[i];
		if (fd >= 3)
			close(fd);
		i++;
	}
	shell->fd_tracker.count = 0;
}
