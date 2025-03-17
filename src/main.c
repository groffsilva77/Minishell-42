/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytavares <ytavares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:14:15 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/03/16 19:34:48 by ytavares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_fd_tracker(t_shell *shell)
{
	int	i;

	printf("=== DEBUG: Descritores abertos no rastreador ===\n");
	for (i = 0; i < shell->fd_tracker.count; i++)
    {
        printf("FD[%d]: %d\n", i, shell->fd_tracker.fds[i]);
    }
    printf("=== FIM DEBUG ===\n");
}

void	cleanup_shell(t_shell *shell)
{
	t_command	*current;

	current = shell->commands;
	while (current)
	{
		if (current->is_heredoc && current->heredoc_fd >= 0)
			close_and_untrack_fd(shell, &current->heredoc_fd);
		current = current->next;
	}
	close_all_tracked_fds(shell);
	free_command_list(shell->commands);
	ft_free(shell);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
		return (1);
	setup_signal_handlers();
	init_fd_tracker(shell);
	shell_loop(shell);
	cleanup_shell(shell);
	return (0);
}
