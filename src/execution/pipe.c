/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:39:05 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/31 17:18:14 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	setup_pipes(t_exec_context *ctx)
{
	if (pipe(ctx->pipe_fds) < 0)
	{
		perror("pipe failed");
		return (-1);
	}
	return (0);
}

void	execute_pipeline(t_command *commands, t_shell *shell)
{
	t_exec_context	ctx;
	int				status;

	ctx.prev_fd = -1;
	while (commands)
	{
		if (commands->next && setup_pipes(&ctx) < 0)
			return ;
		ctx.pid = fork();
		if (ctx.pid < 0)
			return (perror("fork failed"));
		if (ctx.pid == 0)
			create_process(commands, &ctx, shell);
		close(ctx.pipe_fds[1]);
		if (ctx.prev_fd != -1)
			close(ctx.prev_fd);
		ctx.prev_fd = ctx.pipe_fds[0];
		commands = commands->next;
	}
	while (wait(&status) > 0)
		;
	shell->exit_status = WEXITSTATUS(status);
}
