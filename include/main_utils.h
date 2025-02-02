/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:27:31 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/01/31 17:13:52 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_UTILS_H
# define MAIN_UTILS_H

# include "minishell.h"

void		shell_loop(t_shell *shell);
void		execute_and_cleanup(t_command *commands, t_shell *shell);
char		*get_user_input(void);
int			is_empty_input(const char *input);
t_command	*process_input(char *input, t_shell *shell);

#endif