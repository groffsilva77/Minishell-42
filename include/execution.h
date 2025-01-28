/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:38:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/28 18:25:32 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

typedef struct s_exec_context
{
    int		prev_fd;
    int		pipe_fds[2];
	__pid_t	pid;
}	t_exec_context;


void	execute_commands(t_command *commands, t_shell *shell);
int		handle_redirections(t_command *cmd);
void	create_process(t_command *cmd, t_exec_context *ctx, t_shell *shell);
int		setup_pipes(t_exec_context *ctx);
void	execute_pipeline(t_command *commands, t_shell *shell);

#endif