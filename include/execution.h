/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:38:49 by ytavares          #+#    #+#             */
/*   Updated: 2025/01/31 17:13:40 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

void	execute_command(t_command *cmd, t_shell *shell);
void	execute_pipeline(t_command *commands, t_shell *shell);
int		setup_pipes(t_exec_context *ctx);
void	create_process(t_command *cmd, t_exec_context *ctx, t_shell *shell);

int		handle_input_redirection(t_command *cmd);
int		handle_output_redirection(t_command *cmd);
int		setup_redirections(t_command *cmd);
int		handle_redirections(t_command *cmd);

char	*resolve_absolute_path(const char *command);
char	*search_in_path(const char *command, char *path);
char	*find_command_path(const char *command, char **envp);

void	free_commands(t_command *commands, t_shell *shell);

#endif