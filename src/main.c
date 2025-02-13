/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggroff-d <ggroff-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:14:15 by ggroff-d          #+#    #+#             */
/*   Updated: 2025/02/13 17:26:12 by ggroff-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.memory = NULL;
	shell.env_copy = envp;
	shell.exit_status = 0;
	setup_signal_handlers();
	shell_loop(&shell);
	ft_free_all(&shell);
	return (0);
}
