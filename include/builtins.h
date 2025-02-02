/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 11:38:35 by ytavares          #+#    #+#             */
/*   Updated: 2025/02/02 16:20:07 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

//builtins (ptototype)
int	the_echo(char **args, t_shell *shell);
int	the_cd(char **args, t_shell *shell);
int	the_pwd(t_shell *shell);
int	the_env(t_shell *shell);
int	the_export(char **args, t_shell *shell);
int	the_unset(char **args, t_shell *shell);
int	the_exit(char **args, t_shell *shell);

#endif
